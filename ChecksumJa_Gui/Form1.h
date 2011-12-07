#pragma once
#include <windows.h>
#include <time.h>
#include <intrin.h>
#include "FileReader.h"

namespace ChecksumJa_Gui {
	DWORD ( _stdcall *alg_fun)(DWORD aktWart, DWORD bufWsk, DWORD bufLen);
	DWORD static algValue;

	unsigned __int64 rdtsc(void)
	{
		 return __rdtsc();
	}

	extern "C" DWORD _stdcall CRC32_MASM_TAB(DWORD, DWORD, DWORD); 
	extern "C" DWORD _stdcall CRC32_MASM_BITBYBIT(DWORD, DWORD, DWORD); 
	extern "C" DWORD _stdcall ADLER32_MASM(DWORD, DWORD, DWORD); 

	using namespace System;
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
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::ListBox^  logBox;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;


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
				 this->logBox = (gcnew System::Windows::Forms::ListBox());
				 this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
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
				 this->cAlgorytm->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"CRC 32 - MASM TABLE", L"CRC 32 - MASM BIT-By-BIT", 
					 L"CRC 32 - C", L"Adler32 - MASM", L"Alder 32 - C"});
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
				 this->bOblicz->Location = System::Drawing::Point(12, 102);
				 this->bOblicz->Name = L"bOblicz";
				 this->bOblicz->Size = System::Drawing::Size(75, 22);
				 this->bOblicz->TabIndex = 4;
				 this->bOblicz->Text = L"Oblicz ";
				 this->bOblicz->UseVisualStyleBackColor = true;
				 this->bOblicz->Click += gcnew System::EventHandler(this, &Form1::bOblicz_Click);
				 // 
				 // tCzasWykoania
				 // 
				 this->tCzasWykoania->Enabled = false;
				 this->tCzasWykoania->Location = System::Drawing::Point(257, 111);
				 this->tCzasWykoania->Name = L"tCzasWykoania";
				 this->tCzasWykoania->Size = System::Drawing::Size(189, 20);
				 this->tCzasWykoania->TabIndex = 5;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(164, 111);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(87, 13);
				 this->label2->TabIndex = 6;
				 this->label2->Text = L"Czas wykonania:";
				 // 
				 // tWynik
				 // 
				 this->tWynik->Location = System::Drawing::Point(93, 137);
				 this->tWynik->Name = L"tWynik";
				 this->tWynik->Size = System::Drawing::Size(352, 20);
				 this->tWynik->TabIndex = 7;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(47, 137);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(40, 13);
				 this->label3->TabIndex = 8;
				 this->label3->Text = L"Wynik:";
				 // 
				 // logBox
				 // 
				 this->logBox->FormattingEnabled = true;
				 this->logBox->Location = System::Drawing::Point(12, 160);
				 this->logBox->Name = L"logBox";
				 this->logBox->Size = System::Drawing::Size(433, 342);
				 this->logBox->TabIndex = 10;
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
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(457, 512);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->logBox);
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
				 this->logBox->Items->Add("Otwórz plik button ");

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
						 this->logBox->Items->Add("B³¹d otwierania pliku: "+fileReader->getLastError());
						 this->bOblicz->Enabled = FALSE;
					 }
				 }
			 }

	private: System::Void bOblicz_Click(System::Object^  sender, System::EventArgs^  e) {
				 //W tej funkcji powiniœmy mieæ otwarty plik dostêpny przez obiekt fileReader
				 //mo¿emy odczytaæ jego wielkoœæ, iloœæ zaalokowanej pamiêci
				 //odczytaæ ten plik

				 this->logBox->Items->Add("Oblicz button");
				 fileReader->setMaxBufferSize(BufferSizeFromRadioButton());
				 if (fileReader->initBuffer() == FALSE){
					 this->logBox->Items->Add("B³¹d inicjalizacji bufora.");
					 this->groupBox1->Enabled=TRUE;
				 } else {
					 this->logBox->Items->Add("Maksymalny rozmiar bufora: "+fileReader->getMaxBufferSize());
					 this->groupBox1->Enabled=FALSE;
					 this->logBox->Items->Add("Wielkoœæ zaalokowanej pamiêci: "+_msize(fileReader->getData())+" B, "+
						 _msize(fileReader->getData())/(1024*1024) + " MB");
					 this->logBox->Items->Add("Wielkoœæ pliku: "+fileReader->getSize()+" B, "+
						 fileReader->getSize()/(1024*1024) + " MB");
					 this->logBox->Items->Add("Wielkoœæ buffora: "+fileReader->getCurrentBufferSize()+" B, "+
						 (fileReader->getCurrentBufferSize())/(1024*1024) + " MB");
					 this->logBox->Items->Add("Iloœæ czêœci: "+fileReader->getHowManyParts());
				 }
				 __int64 cycleCounter = rdtsc();
				 int allTime = 0;
				 int startTime, endTime, totalTime;
				 for (int i=0; i<fileReader->getHowManyParts(); i++){
					 startTime = time(NULL);
					 int wasRead = fileReader->read();
					 if (alg_fun != NULL){
						 algValue = alg_fun(algValue,(DWORD) fileReader->getData(), wasRead);
					 } else {
						this->logBox->Items->Add("B³¹d nie wybrano algorytmu. ");
					 }
					 endTime = time(NULL);
					 totalTime = endTime - startTime;
					 this->logBox->Items->Add("Przeczytano nr. , iloœæ: "+i+" , "+wasRead);
					 this->logBox->Items->Add("Czas czytania: "+totalTime);
					 this->logBox->Items->Add("Iloœc cykli: "+(rdtsc()-cycleCounter) );
					 allTime += totalTime;
				 }
				 //String^ str = gcnew System::String();
				 //str = Convert::ToString((int)algValue);
				 int z = algValue;
				 //this->tWynik->Text= Convert::ToString((unsigned int)algValue);
				 //String str = Convert::ToString(z,16);
				 this->tWynik->Text= Convert::ToString(z,16)->ToUpper();
				 this->logBox->Items->Add("Czas ³¹czny: "+allTime);
				 this->groupBox1->Enabled=TRUE;
				 algValue=0;
				 fileReader->resetFile();
			 }

	private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 //Ta metoda jest wywo³ywana przy zamykaniu okna.
				 //U¿ywam jej aby wywo³aæ destruktory klas nie zarz¹dzanych przez CLI/.NET
				 if (fileReader!=NULL){
					 delete fileReader;
				 }
			 }
	private: int BufferSizeFromRadioButton(){
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
				//this->cAlgorytm->SelectedIndex == -1 -> Nothing chossed
				 this->logBox->Items->Add("Numer opcji: "+this->cAlgorytm->SelectedIndex);
				 switch(this->cAlgorytm->SelectedIndex){
					case 0:	alg_fun=CRC32_MASM_TAB; algValue=0; break;
					case 1:	alg_fun=CRC32_MASM_BITBYBIT; algValue=0; break;
					case 3: alg_fun=ADLER32_MASM; algValue=0; break;
					default: alg_fun=NULL; algValue=0;
				 }

			 }
};
}