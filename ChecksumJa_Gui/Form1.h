#pragma once
#include <windows.h>
#include <intrin.h>
#include "FileReader.h"

namespace ChecksumJa_Gui {
	DWORD ( _stdcall *alg_fun)(DWORD aktWart, DWORD bufWsk, DWORD bufLen);
	DWORD static algValue;

	extern "C" DWORD _stdcall CRC32_MASM_TAB(DWORD, DWORD, DWORD); 
	extern "C" DWORD _stdcall CRC32_MASM_BITBYBIT(DWORD, DWORD, DWORD); 
	extern "C" DWORD _stdcall ADLER32_MASM(DWORD, DWORD, DWORD); 
	extern "C" DWORD _stdcall ADLER32_VECT(DWORD, DWORD, DWORD); 

unsigned long crc32_tab[256] =
{
  0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
  0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
  0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
  0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
  0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
  0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
  0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
  0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
  0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
  0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
  0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
  0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
  0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
  0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
  0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
  0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
  0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
  0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
  0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
  0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
  0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
  0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
  0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
  0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
  0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
  0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
  0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
  0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
  0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
  0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
  0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
  0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
  0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
  0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
  0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
  0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
  0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
  0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
  0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
  0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
  0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
  0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
  0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
  0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
  0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
  0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
  0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
  0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
  0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
  0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
  0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
  0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
  0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
  0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
  0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
  0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
  0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
  0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
  0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
  0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
  0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
  0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
  0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
  0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

DWORD _stdcall Crc32ByTab(DWORD crc, DWORD bufor, DWORD len){
	unsigned long crc32;
	int length = (int) len;
	unsigned char *buf = (unsigned char*) bufor;

	if (crc == 0){
		//Zaczynamy nowe obliczenie, startujemy od 0
		crc32 = 0xffffffff;
	} else {
		//Dostaliœmy jak¹œ wartoœæ. Czyli by³y jakieœ obliczenia.
		crc32 = (unsigned long)crc;
		crc32 ^= 0xffffffff;
	}
	
	//Dla ca³ego otrzymanego bufora
	for(int i = 0; i < length; i++){
        crc32 = (crc32 >> 8) ^ crc32_tab[(crc32 & 0xff) ^ buf[i]];
    }
 
    crc32 ^= 0xffffffff;
	return crc32;
}


#define MOD_ADLER 65521 
DWORD _stdcall adler32(DWORD adler, DWORD bufor, DWORD len)
//(unsigned char *data, int len) 
{
	unsigned char *buf = (unsigned char*) bufor;
	int length = (int) len;
	unsigned long a = 1, b = 0;

	//Rozbicie sumy na podsumy
	if(adler != 0){
		a = adler & 0xffff;
		b = (adler >> 16) & 0xffff;
	}
    int i;
 
    //Dla ka¿dego bajtu
    for (i = 0; i < length; ++i)
    {
        a = (a + buf[i]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
 
    return (b << 16) | a;
}

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tNazwaPliku;
	protected: 

	private: System::Windows::Forms::Button^  bOtworzPlik;
	private: System::Windows::Forms::ComboBox^  cAlgorytm;
	protected: 


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  bOblicz;
	private: System::Windows::Forms::TextBox^  tCzasWykoania;



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tWynik;

	private: System::Windows::Forms::Label^  label3;

	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  tLiczbaCykliZegara;


			 FileReader* fileReader;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->tNazwaPliku = (gcnew System::Windows::Forms::TextBox());
				 this->bOtworzPlik = (gcnew System::Windows::Forms::Button());
				 this->cAlgorytm = (gcnew System::Windows::Forms::ComboBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->bOblicz = (gcnew System::Windows::Forms::Button());
				 this->tCzasWykoania = (gcnew System::Windows::Forms::TextBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->tWynik = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->tLiczbaCykliZegara = (gcnew System::Windows::Forms::TextBox());
				 this->groupBox1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // tNazwaPliku
				 // 
				 this->tNazwaPliku->Enabled = false;
				 this->tNazwaPliku->Location = System::Drawing::Point(94, 15);
				 this->tNazwaPliku->Name = L"tNazwaPliku";
				 this->tNazwaPliku->Size = System::Drawing::Size(352, 20);
				 this->tNazwaPliku->TabIndex = 0;
				 // 
				 // bOtworzPlik
				 // 
				 this->bOtworzPlik->Location = System::Drawing::Point(12, 15);
				 this->bOtworzPlik->Name = L"bOtworzPlik";
				 this->bOtworzPlik->Size = System::Drawing::Size(75, 23);
				 this->bOtworzPlik->TabIndex = 1;
				 this->bOtworzPlik->Text = L"Otwórz plik";
				 this->bOtworzPlik->UseVisualStyleBackColor = true;
				 this->bOtworzPlik->Click += gcnew System::EventHandler(this, &Form1::bOtworzPlik_Click);
				 // 
				 // cAlgorytm
				 // 
				 this->cAlgorytm->FormattingEnabled = true;
				 this->cAlgorytm->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"CRC 32 - MASM - bit po bicie", L"CRC 32 - MASM - tablicowo", 
					 L"CRC 32 - C - tablicowo", L"Adler32 - MASM - klasycznie", L"Alder32 - MASM z optymalizacj¹", L"Adler32 - C - klasycznie"});
				 this->cAlgorytm->Location = System::Drawing::Point(94, 41);
				 this->cAlgorytm->Name = L"cAlgorytm";
				 this->cAlgorytm->Size = System::Drawing::Size(352, 21);
				 this->cAlgorytm->TabIndex = 2;
				 this->cAlgorytm->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cAlgorytm_SelectedIndexChanged);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(35, 44);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(53, 13);
				 this->label1->TabIndex = 3;
				 this->label1->Text = L"Algorytm: ";
				 // 
				 // bOblicz
				 // 
				 this->bOblicz->CausesValidation = false;
				 this->bOblicz->Enabled = false;
				 this->bOblicz->FlatStyle = System::Windows::Forms::FlatStyle::System;
				 this->bOblicz->Location = System::Drawing::Point(12, 114);
				 this->bOblicz->Name = L"bOblicz";
				 this->bOblicz->Size = System::Drawing::Size(75, 69);
				 this->bOblicz->TabIndex = 4;
				 this->bOblicz->Text = L"Oblicz ";
				 this->bOblicz->UseVisualStyleBackColor = true;
				 this->bOblicz->Click += gcnew System::EventHandler(this, &Form1::bOblicz_Click);
				 // 
				 // tCzasWykoania
				 // 
				 this->tCzasWykoania->Location = System::Drawing::Point(188, 114);
				 this->tCzasWykoania->Name = L"tCzasWykoania";
				 this->tCzasWykoania->Size = System::Drawing::Size(257, 20);
				 this->tCzasWykoania->TabIndex = 5;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(97, 121);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(87, 13);
				 this->label2->TabIndex = 6;
				 this->label2->Text = L"Czas wykonania:";
				 // 
				 // tWynik
				 // 
				 this->tWynik->Location = System::Drawing::Point(188, 163);
				 this->tWynik->Name = L"tWynik";
				 this->tWynik->Size = System::Drawing::Size(258, 20);
				 this->tWynik->TabIndex = 7;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(97, 170);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(40, 13);
				 this->label3->TabIndex = 8;
				 this->label3->Text = L"Wynik:";
				 // 
				 // radioButton1
				 // 
				 this->radioButton1->AutoSize = true;
				 this->radioButton1->Location = System::Drawing::Point(6, 12);
				 this->radioButton1->Name = L"radioButton1";
				 this->radioButton1->Size = System::Drawing::Size(47, 17);
				 this->radioButton1->TabIndex = 11;
				 this->radioButton1->TabStop = true;
				 this->radioButton1->Text = L"2MB";
				 this->radioButton1->UseVisualStyleBackColor = true;
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(12, 82);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(81, 13);
				 this->label4->TabIndex = 12;
				 this->label4->Text = L"Rozmiar bufora:";
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->radioButton6);
				 this->groupBox1->Controls->Add(this->radioButton5);
				 this->groupBox1->Controls->Add(this->radioButton4);
				 this->groupBox1->Controls->Add(this->radioButton3);
				 this->groupBox1->Controls->Add(this->radioButton2);
				 this->groupBox1->Controls->Add(this->radioButton1);
				 this->groupBox1->Location = System::Drawing::Point(100, 70);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(345, 35);
				 this->groupBox1->TabIndex = 13;
				 this->groupBox1->TabStop = false;
				 // 
				 // radioButton6
				 // 
				 this->radioButton6->AutoSize = true;
				 this->radioButton6->Checked = true;
				 this->radioButton6->Location = System::Drawing::Point(284, 12);
				 this->radioButton6->Name = L"radioButton6";
				 this->radioButton6->Size = System::Drawing::Size(59, 17);
				 this->radioButton6->TabIndex = 16;
				 this->radioButton6->TabStop = true;
				 this->radioButton6->Text = L"100MB";
				 this->radioButton6->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				 this->radioButton6->UseVisualStyleBackColor = true;
				 // 
				 // radioButton5
				 // 
				 this->radioButton5->AutoSize = true;
				 this->radioButton5->Location = System::Drawing::Point(225, 12);
				 this->radioButton5->Name = L"radioButton5";
				 this->radioButton5->Size = System::Drawing::Size(53, 17);
				 this->radioButton5->TabIndex = 15;
				 this->radioButton5->TabStop = true;
				 this->radioButton5->Text = L"64MB";
				 this->radioButton5->UseVisualStyleBackColor = true;
				 // 
				 // radioButton4
				 // 
				 this->radioButton4->AutoSize = true;
				 this->radioButton4->Location = System::Drawing::Point(174, 12);
				 this->radioButton4->Name = L"radioButton4";
				 this->radioButton4->Size = System::Drawing::Size(53, 17);
				 this->radioButton4->TabIndex = 14;
				 this->radioButton4->TabStop = true;
				 this->radioButton4->Text = L"32MB";
				 this->radioButton4->UseVisualStyleBackColor = true;
				 // 
				 // radioButton3
				 // 
				 this->radioButton3->AutoSize = true;
				 this->radioButton3->Location = System::Drawing::Point(114, 12);
				 this->radioButton3->Name = L"radioButton3";
				 this->radioButton3->Size = System::Drawing::Size(53, 17);
				 this->radioButton3->TabIndex = 13;
				 this->radioButton3->TabStop = true;
				 this->radioButton3->Text = L"16MB";
				 this->radioButton3->UseVisualStyleBackColor = true;
				 // 
				 // radioButton2
				 // 
				 this->radioButton2->AutoSize = true;
				 this->radioButton2->Location = System::Drawing::Point(60, 12);
				 this->radioButton2->Name = L"radioButton2";
				 this->radioButton2->Size = System::Drawing::Size(47, 17);
				 this->radioButton2->TabIndex = 12;
				 this->radioButton2->TabStop = true;
				 this->radioButton2->Text = L"8MB";
				 this->radioButton2->UseVisualStyleBackColor = true;
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(97, 147);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(67, 13);
				 this->label5->TabIndex = 14;
				 this->label5->Text = L"Cykli zegara:";
				 // 
				 // tLiczbaCykliZegara
				 // 
				 this->tLiczbaCykliZegara->Location = System::Drawing::Point(188, 140);
				 this->tLiczbaCykliZegara->Name = L"tLiczbaCykliZegara";
				 this->tLiczbaCykliZegara->Size = System::Drawing::Size(258, 20);
				 this->tLiczbaCykliZegara->TabIndex = 15;
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(457, 203);
				 this->Controls->Add(this->tLiczbaCykliZegara);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->tWynik);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->tCzasWykoania);
				 this->Controls->Add(this->bOblicz);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->cAlgorytm);
				 this->Controls->Add(this->bOtworzPlik);
				 this->Controls->Add(this->tNazwaPliku);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"Form1";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"CRC32 - Adler32  - Jêzyki Asemblerowe";
				 this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void bOtworzPlik_Click(System::Object^  sender, System::EventArgs^  e) {

				 this->bOblicz->Enabled = TRUE;

				 //Wywo³aj dialogo otwierania pliku
				 OpenFileDialog^ opfdlg=gcnew OpenFileDialog ();
				 //U¿ytkownik wyszed³ przez OK
				 if(opfdlg->ShowDialog()==::System::Windows::Forms::DialogResult::OK){
					 //Nazwa pliku w oknie
					 this->tNazwaPliku->Text=opfdlg->FileName;
					 //Jeœli wczeœniej otwarliœmy jakiœ plik pora skasowaæ jego obiekt
					 if (fileReader != NULL){
						 delete fileReader;
					 }

					 //Nowy obiekt do zarz¹dzania otwieranym plikiem
					 using namespace System::Runtime::InteropServices;
					 char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(opfdlg->FileName);
					 fileReader = new FileReader(str);
					 if (fileReader->openFile()==FALSE){
						 //this->logBox->Items->Add("B³¹d otwierania pliku: "+fileReader->getLastError());
						 this->bOblicz->Enabled = FALSE;
					 }
				 }
			 }

			 void afterOblicz(){
			 	this->groupBox1->Enabled=TRUE;
				 algValue=0;
				 if (alg_fun == ADLER32_MASM || alg_fun == ADLER32_VECT){
					 algValue=1;
				 }
				 fileReader->resetFile();
			 }

	private: System::Void bOblicz_Click(System::Object^  sender, System::EventArgs^  e) {
				 /*
				 W tej funkcji powiniœmy mieæ otwarty plik dostêpny przez obiekt fileReader
				 mo¿emy odczytaæ jego wielkoœæ, iloœæ zaalokowanej pamiêci
				 odczytaæ ten plik

				 Obliczamy wartoœæ konkretnej interesuj¹cej funkcji.
				 */

				 fileReader->setMaxBufferSize(BufferSizeFromRadioButton()); //Ustaw wielkoœæ bufora

				 if (fileReader->initBuffer() == FALSE){
					 //this->logBox->Items->Add("B³¹d inicjalizacji bufora.");
					 this->groupBox1->Enabled=TRUE;
				 } else 
				 //Wyœwietlamy informacjie o pliku
				 {
					 //this->logBox->Items->Add("Maksymalny rozmiar bufora: "+fileReader->getMaxBufferSize());
					 this->groupBox1->Enabled=FALSE;
					// this->logBox->Items->Add("Wielkoœæ zaalokowanej pamiêci: "+_msize(fileReader->getData())+" B, "+
						// _msize(fileReader->getData())/(1024*1024) + " MB");
					// this->logBox->Items->Add("Wielkoœæ pliku: "+fileReader->getSize()+" B, "+
						// fileReader->getSize()/(1024*1024) + " MB");
					// this->logBox->Items->Add("Wielkoœæ buffora: "+fileReader->getCurrentBufferSize()+" B, "+
						 //(fileReader->getCurrentBufferSize())/(1024*1024) + " MB");
					// this->logBox->Items->Add("Iloœæ czêœci: "+fileReader->getHowManyParts());
				 }


				 //Rozpoczynamy obliczenia i pomiar czasu
				 Stopwatch ^ stopwatch = Stopwatch::StartNew();
				 stopwatch->StartNew();
				 for (int i=0; i<fileReader->getHowManyParts(); i++){
					 int wasRead = fileReader->read();
					 if (alg_fun != NULL){
						 algValue = alg_fun(algValue,(DWORD) fileReader->getData(), wasRead);
					 } else {
						// this->logBox->Items->Add("B³¹d nie wybrano algorytmu. ");
						   MessageBox::Show("Nale¿y wybraæ algorytm.", this->Text , MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
						   afterOblicz();
						   return;
					 }
					 //this->logBox->Items->Add("Przeczytano nr. , iloœæ: "+i+" , "+wasRead);
				 }
				 stopwatch->Stop();
				 this->tCzasWykoania->Text=Convert::ToString((long long)(stopwatch->ElapsedMilliseconds));
				 this->tLiczbaCykliZegara->Text=Convert::ToString((long long)(stopwatch->ElapsedTicks));
				 stopwatch->Reset();
				 int z = algValue;
				 this->tWynik->Text= Convert::ToString(z,16)->ToUpper();
			afterOblicz();
			 }
	

	private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 /*
				 Ta metoda jest wywo³ywana przy zamykaniu okna.
				 U¿ywam jej aby wywo³aæ destruktory klas nie zarz¹dzanych przez CLI/.NET
				 */
				 if (fileReader!=NULL){
					 delete fileReader;
				 }
			 }
	private: int BufferSizeFromRadioButton(){
				 /*
					Zmiana wielkoœci bufroa na dane wczytane z pliku.
				 */
				 int bufferSize = 100*1024*1024;
				 if (this->radioButton1->Checked){
					 bufferSize = 2*1024*1024;
				 } else if (this->radioButton2->Checked) {
					 bufferSize = 8*1024*1024;
				 } else if (this->radioButton3->Checked) {
					 bufferSize = 16*1024*1024;
				 } else if (this->radioButton4->Checked) {
					 bufferSize = 32*1024*1024;
				 } else if (this->radioButton5->Checked) {
					 bufferSize = 64*1024*1024;
				 } else if (this->radioButton6->Checked) {
					 bufferSize = 100*1024*1024;
				 }
				 return bufferSize;
			 }

	private: System::Void cAlgorytm_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 /*
					Zmiana wybranego algorytmu.
				 */
				 //this->cAlgorytm->SelectedIndex == -1 -> Nothing chossed
				 //this->logBox->Items->Add("Numer opcji: "+this->cAlgorytm->SelectedIndex);
				/*
				CRC 32 - MASM - bit po bicie
				CRC 32 - MASM - tablicowo
				CRC 32 - C - tablicowo
				Adler32 - MASM - klasycznie
				Alder32 - MASM z optymalizacj¹
				Adler32 - C - klasycznie
				*/
				 switch(this->cAlgorytm->SelectedIndex){
					case 0:alg_fun=CRC32_MASM_BITBYBIT; algValue=0; break;
					case 1:	alg_fun=CRC32_MASM_TAB; algValue=0; break;
					case 2: alg_fun=Crc32ByTab; algValue=0; break;
					case 3:	alg_fun=ADLER32_MASM; algValue=1; break;
					case 4: alg_fun=ADLER32_VECT; algValue=1; break;
					case 5: alg_fun=adler32; algValue=0; break;
					default: alg_fun=NULL; algValue=1;
				 }

			 }
	};
}