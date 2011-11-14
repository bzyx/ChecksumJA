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
	//Zwrca true jeœli otworzenie pliku siê powiedzie.
	this->lastError=NO_ERROR;

	//Tworzymy tymczasowo obiekt typu string
	std::string tmpStr = std::string(this->fileName);

	//Funckcja tworzenia uchwyu wymaga LPCWSTR
#ifdef UNICODE
	//Jeœli œrodowisko dzia³a jakos UNICODE
	//Tworzymy WSTRING -> WCHAR
	std::wstring stemp = s2ws(tmpStr);
	LPCWSTR result = stemp.c_str();
#else
	LPCWSTR result = tmpStr.c_str();
#endif

	this->hFile = CreateFile(result,			// Nazwa pliku
		GENERIC_READ,							// Plik do odczytu
		FILE_SHARE_READ,						// Wspó³dzielenie pliku w trybie do odczytu 
												//-> by³ error ERROR_SHARING_VIOLATION
		NULL,									// No security
		OPEN_EXISTING,							// Tylko istniej¹ce pliki
		FILE_ATTRIBUTE_NORMAL					// Normal file (wartoœæ domyœlna) 
		| FILE_FLAG_NO_BUFFERING,				//+ wy³¹czenie buforowania					
		0);										// Dla otwierania istniej¹cego pliku ignorowany parametr
	//Ostatni b³¹d jeœli wyst¹pi³ przy tworzeniu uchwytu
	this->lastError=GetLastError();
	if (this->hFile == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	//Odczyt wielkoœci pliku. Konieczne u¿ycie funkcji WinAPI, gdy¿ fseek nie obs³uguje plików >2GB
	this->size=GetFileSizeWA();
	if (this->size == -1){
		//W lastError znajduje siê wartoœæ b³êdu
		return FALSE;
	}
	//Po odczytaniu wielkoœci pliku ten uchwyt nie bêdzie ju¿ potrzebny.
	CloseHandle(this->hFile);
	this->hFile = NULL;
	if (this->size == -1){
		//W lastError znajduje siê wartoœæ b³êdu
		return FALSE;
	}

	//Otwieranie pliku w stylu C -> do zmiennej FILE
	this->file = fopen(this->fileName, "rb");
	if ( this->file == NULL ){
		//B³êdy zwi¹zane z WinAPI maj¹ wartoœci >= 0. 
		this->lastError=-1;
		return FALSE;
	}
	
	//Uda³o siê.
	return TRUE;
}

void FileReader::resetFile(){
	//Jeœli chcemy dzia³aæ na tym samym pliku
	//musimy cofn¹æ zmienn¹ FILE znów na pocz¹tek
	rewind(this->file);
}
bool FileReader::initBuffer(){
	//Inicjalizuje bufor na wczywane dane

	// Jeœli bufor jest pusty, lub jego wielkoœæ nie jest taka jakiej oczekujemy,
	// tzn. np. gdy zmieniliœmy ¿¹dany rozmiar wieloœæi bufora miêdzy jednym plikiem a drugim
	if (   (this->fileBuffer == NULL )
		|| (this->currentBufferSize != FileReader::MAX_BUFFER_SIZE) 
		|| (this->currentBufferSize != this->size) ){

			//po pierwsze powiniœmy usun¹æ istniej¹cy bufor jeœli ju¿ mia³ jak¹œ wartoœæ
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
	//bêdzie musia³ byæ plik odczytany
	this->howManyParts = size/currentBufferSize;
	if ( (size % currentBufferSize) != 0 ){
		//Jeœli wielkoœæ pliku nie jest wielkotnoœci¹ wielkoœci bufora
		this->howManyParts+=1;
	}
	return TRUE;

}

int FileReader::read(){
	this->lastError = NO_ERROR;
	//Odczytywanie pliku 
	//FILE "wie" gdzie zakoñczy³ czytanie, wiêc sukcesywne wywo³ywanie tej funkcji spowoduje
	// przeczytanie ca³ego pliku. W howMuchWasRead znajduje siê wartoœæ faktycznej iloœci odczytanych bajtów.
	int howMuchWasRead = fread(this->fileBuffer,
		sizeof(this->fileBuffer[0]),
		this->currentBufferSize,
		this->file);

	return howMuchWasRead;
}

void FileReader::closeFile(){
	//Zamkniêcie pliku i jego ew. uchwytów
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
	//Zwraca wskaŸnik na pocz¹tek bufora
	return this->fileBuffer;
}



FileReader::~FileReader(void) {
	//Destruktor
	//Zamykamy plik, a póŸniej kasujemy bufor
	this->closeFile();
	if (fileBuffer != NULL)
		delete[] fileBuffer;
}

int FileReader::getCurrentBufferSize(){
	//Zwraca aktualny rozmiar bufora
	return this->currentBufferSize;
}

int FileReader::getHowManyParts(){
	//Zwraca iloœæ czêœci na jakie plik zosta³ podzielony
	return this->howManyParts;
}

DWORD FileReader::getLastError(){
	//Zwraca wartoœæ b³êdu jeœli taki wyst¹pi³
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
	//Wywo³anie funkcji WinAPI, aby uzyskaæ rozmiar pliku
	this->lastError=NO_ERROR;

	if (this->hFile!=INVALID_HANDLE_VALUE){
		LARGE_INTEGER DataTemp;
		if (GetFileSizeEx(hFile,&DataTemp) == 0){
			this->lastError=GetLastError();
			return -1;
		}
		//Jeœli nie by³o b³êdu
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