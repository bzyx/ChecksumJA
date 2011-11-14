#include "StdAfx.h"
#include "FileReader.h"

std::wstring s2ws(const std::string& s);

int FileReader::MAX_BUFFER_SIZE = 100*1024*1024;

FileReader::FileReader(char* fileName)
{
	this->fileName = fileName;
	this->fileBuffer = NULL;
	this->hFile = INVALID_HANDLE_VALUE;
	this->lastError = NO_ERROR;
	this->size = -1;
	this->currentBufferSize=-1;
	this->file = NULL;
}

bool FileReader::openFile(){
	//Otwiera plik -> tworzy uchwyt do tego pliku.
	//Zwrca true je�li otworzenie pliku si� powiedzie.
	this->lastError=NO_ERROR;

	//Tworzymy tymczasowo obiekt typu string
	std::string tmpStr = std::string(this->fileName);

	//Funckcja tworzenia uchwyu wymaga LPCWSTR
#ifdef UNICODE
	//Je�li �rodowisko dzia�a jakos UNICODE
	//Tworzymy WSTRING -> WCHAR
	std::wstring stemp = s2ws(tmpStr);
	LPCWSTR result = stemp.c_str();
#else
	LPCWSTR result = tmpStr.c_str();
#endif

	this->hFile = CreateFile(result,			// Nazwa pliku
		GENERIC_READ,							// Plik do odczytu
		FILE_SHARE_READ,						// Wsp�dzielenie pliku w trybie do odczytu 
												//-> by� error ERROR_SHARING_VIOLATION
		NULL,									// No security
		OPEN_EXISTING,							// Tylko istniej�ce pliki
		FILE_ATTRIBUTE_NORMAL					// Normal file (warto�� domy�lna) 
		| FILE_FLAG_NO_BUFFERING,				//+ wy��czenie buforowania					
		0);										// Dla otwierania istniej�cego pliku ignorowany parametr
	//Ostatni b��d je�li wyst�pi� przy tworzeniu uchwytu
	this->lastError=GetLastError();
	if (this->hFile == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	//Odczyt wielko�ci pliku. Konieczne u�ycie funkcji WinAPI, gdy� fseek nie obs�uguje plik�w >2GB
	this->size=GetFileSizeWA();
	if (this->size == -1){
		//W lastError znajduje si� warto�� b��du
		return FALSE;
	}
	//Po odczytaniu wielko�ci pliku ten uchwyt nie b�dzie ju� potrzebny.
	CloseHandle(this->hFile);
	this->hFile = NULL;
	if (this->size == -1){
		//W lastError znajduje si� warto�� b��du
		return FALSE;
	}

	//Otwieranie pliku w stylu C -> do zmiennej FILE
	this->file = fopen(this->fileName, "rb");
	if ( this->file == NULL ){
		//B��dy zwi�zane z WinAPI maj� warto�ci >= 0. 
		this->lastError=-1;
		return FALSE;
	}
	
	//Uda�o si�.
	return TRUE;
}

void FileReader::resetFile(){
	//Je�li chcemy dzia�a� na tym samym pliku
	//musimy cofn�� zmienn� FILE zn�w na pocz�tek
	rewind(this->file);
}
bool FileReader::initBuffer(){
	//Inicjalizuje bufor na wczywane dane

	// Je�li bufor jest pusty, lub jego wielko�� nie jest taka jakiej oczekujemy,
	// tzn. np. gdy zmienili�my ��dany rozmiar wielo��i bufora mi�dzy jednym plikiem a drugim
	if (   (this->fileBuffer == NULL )
		|| (this->currentBufferSize != FileReader::MAX_BUFFER_SIZE) 
		|| (this->currentBufferSize != this->size) ){

			//po pierwsze powini�my usun�� istniej�cy bufor je�li ju� mia� jak�� warto��
			if (this->fileBuffer != NULL)
				delete[] this->fileBuffer;

			if ( this->size < FileReader::MAX_BUFFER_SIZE ){
				try {
					this->fileBuffer = new char[this->size];
				} catch(std::bad_alloc&) {
					this->lastError=ERROR_ALLOTTED_SPACE_EXCEEDED;
					return FALSE;
				}
				this->currentBufferSize = this->size;
			} else{
				try {
					this->fileBuffer = new char[FileReader::MAX_BUFFER_SIZE];
				} catch(std::bad_alloc&) {
					this->lastError=ERROR_ALLOTTED_SPACE_EXCEEDED;
					return FALSE;
				}
				this->currentBufferSize = FileReader::MAX_BUFFER_SIZE;
			}
	}

	//Obliczenie ile razy dla wybranego rozmiaru bufora
	//b�dzie musia� by� plik odczytany
	this->howManyParts = size/currentBufferSize;
	if ( (size % currentBufferSize) != 0 ){
		//Je�li wielko�� pliku nie jest wielkotno�ci� wielko�ci bufora
		this->howManyParts+=1;
	}
	return TRUE;

}

int FileReader::read(){
	this->lastError = NO_ERROR;
	//Odczytywanie pliku 
	//FILE "wie" gdzie zako�czy� czytanie, wi�c sukcesywne wywo�ywanie tej funkcji spowoduje
	// przeczytanie ca�ego pliku. W howMuchWasRead znajduje si� warto�� faktycznej ilo�ci odczytanych bajt�w.
	int howMuchWasRead = fread(this->fileBuffer,
		sizeof(this->fileBuffer[0]),
		this->currentBufferSize,
		this->file);

	return howMuchWasRead;
}

void FileReader::closeFile(){
	//Zamkni�cie pliku i jego ew. uchwyt�w
	if (this->hFile && (this->hFile != INVALID_HANDLE_VALUE) ){
		CloseHandle(this->hFile);
		this->hFile = NULL;
	}
	fclose(this->file);
	this->file=NULL;
}

__int64 FileReader::getSize(){
	//Zwraca rozmiar pliku w bajtach
	return this->size;
}

char* FileReader::getData(){
	//Zwraca wska�nik na pocz�tek bufora
	return this->fileBuffer;
}



FileReader::~FileReader(void) {
	//Destruktor
	//Zamykamy plik, a p�niej kasujemy bufor
	this->closeFile();
	if (fileBuffer != NULL)
		delete[] fileBuffer;
}

int FileReader::getCurrentBufferSize(){
	//Zwraca aktualny rozmiar bufora
	return this->currentBufferSize;
}

int FileReader::getHowManyParts(){
	//Zwraca ilo�� cz�ci na jakie plik zosta� podzielony
	return this->howManyParts;
}

DWORD FileReader::getLastError(){
	//Zwraca warto�� b��du je�li taki wyst�pi�
	return lastError;
}

void FileReader::setMaxBufferSize(int maxBufferSize){
	//Ustawia maksymalny rozmiar bufora
	FileReader::MAX_BUFFER_SIZE=maxBufferSize;
}

int FileReader::getMaxBufferSize(){
	//Zwraca ustawiony maksymalny rozmiar bufora
	return FileReader::MAX_BUFFER_SIZE;
}

__int64 FileReader::GetFileSizeWA(){
	//Wywo�anie funkcji WinAPI, aby uzyska� rozmiar pliku
	this->lastError=NO_ERROR;

	if (this->hFile!=INVALID_HANDLE_VALUE){
		LARGE_INTEGER DataTemp;
		if (GetFileSizeEx(hFile,&DataTemp) == 0){
			this->lastError=GetLastError();
			return -1;
		}
		//Je�li nie by�o b��du
		return DataTemp.QuadPart;
	} 
	return -1;

}

//Konwersja z Stringa na WSTRING potrzebne do LPCWSTR
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}