#pragma once
#include "Dipole_radiation_pattern.h"


#define release(e,sender) UNREFERENCED_PARAMETER(e),UNREFERENCED_PARAMETER(sender);
#define set_text(label, txt, value) try {label->Text = txt + System::Convert::ToString(value);} catch (...) {MessageBox::Show(L"Плохое значение!");}
#define set_text_back(label, txt, value, back) try {label->Text = txt + System::Convert::ToString(value) + back;} catch (...) {MessageBox::Show(L"Плохое значение!");}
#define enable(element) element->Enabled = true;
#define disable(element) element->Enabled = false;


struct Mouse_position
{
	int x;
	int y;
};

std::pair<Vertex, Vertex> Etheta_vector;
std::pair<Vertex, Vertex> Erad_vector;
std::pair<Vertex, Vertex> Hphi_vector;


std::vector<Vertex> electic_field_line;
std::vector<Vertex> magnetic_field_line;
std::vector<bool> parameters(6, true);

namespace Dipole_Pattern {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Dipole_Face
	/// </summary>
	public ref class Dipole_Face : public System::Windows::Forms::Form
	{
	public:
		Dipole_Face(void)
		{
			rotation = false;
			active = false;
			shift = false;
			gl = new GL;
			MouseXY = new Mouse_position;
			MouseXY->x = 0;
			MouseXY->y = 0;
			dr = new Dipole_radiation;
			status = true;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Dipole_Face()
		{
			if (components)
			{
				delete gl;
				delete MouseXY;
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  GL_Render_Timer;
	private: GL * gl;
	private: Dipole_radiation * dr;
	private: bool active;
	private: bool rotation;
	private: bool shift;
	private: bool status;
	private: Mouse_position * MouseXY;
	private: System::Windows::Forms::Panel^  Pattern_Panel;
	private: System::Windows::Forms::GroupBox^  Head_coordinates;
	private: System::Windows::Forms::Label^  y_location_label;
	private: System::Windows::Forms::Label^  x_location_label;
	private: System::Windows::Forms::Label^  z_location_label;
	private: System::Windows::Forms::Label^  scale_label;
	private: System::Windows::Forms::GroupBox^  Zone;
	private: System::Windows::Forms::RadioButton^  Distant_Button;
	private: System::Windows::Forms::RadioButton^  Near_Button;
	private: System::ComponentModel::BackgroundWorker^  Сalculates_flow;
	private: System::Windows::Forms::Button^  Change_button;
	private: System::Windows::Forms::TextBox^  amperage_box;
	private: System::Windows::Forms::GroupBox^  Parameters;
	private: System::Windows::Forms::GroupBox^  Amperage;
	private: System::Windows::Forms::GroupBox^  Rad;
	private: System::Windows::Forms::GroupBox^  Time;
	private: System::Windows::Forms::GroupBox^  Frequency;
	private: System::Windows::Forms::GroupBox^  Wawelength;
	private: System::Windows::Forms::GroupBox^  Lenght;
	private: System::Windows::Forms::TextBox^  length_box;
	private: System::Windows::Forms::TextBox^  rad_box;
	private: System::Windows::Forms::TextBox^  time_box;
	private: System::Windows::Forms::TextBox^  frequency_box;
	private: System::Windows::Forms::TextBox^  wawelenght_box;
	private: System::Windows::Forms::GroupBox^  Pattern_box;
	private: System::Windows::Forms::GroupBox^  amplitude_Box;
	private: System::Windows::Forms::Label^  erad_label;
	private: System::Windows::Forms::Label^  hphi_label;
	private: System::Windows::Forms::Label^  etheta_label;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->GL_Render_Timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->Pattern_Panel = (gcnew System::Windows::Forms::Panel());
			this->Head_coordinates = (gcnew System::Windows::Forms::GroupBox());
			this->z_location_label = (gcnew System::Windows::Forms::Label());
			this->y_location_label = (gcnew System::Windows::Forms::Label());
			this->x_location_label = (gcnew System::Windows::Forms::Label());
			this->scale_label = (gcnew System::Windows::Forms::Label());
			this->Zone = (gcnew System::Windows::Forms::GroupBox());
			this->Distant_Button = (gcnew System::Windows::Forms::RadioButton());
			this->Near_Button = (gcnew System::Windows::Forms::RadioButton());
			this->Сalculates_flow = (gcnew System::ComponentModel::BackgroundWorker());
			this->Change_button = (gcnew System::Windows::Forms::Button());
			this->amperage_box = (gcnew System::Windows::Forms::TextBox());
			this->Parameters = (gcnew System::Windows::Forms::GroupBox());
			this->Rad = (gcnew System::Windows::Forms::GroupBox());
			this->rad_box = (gcnew System::Windows::Forms::TextBox());
			this->Amperage = (gcnew System::Windows::Forms::GroupBox());
			this->Time = (gcnew System::Windows::Forms::GroupBox());
			this->time_box = (gcnew System::Windows::Forms::TextBox());
			this->Lenght = (gcnew System::Windows::Forms::GroupBox());
			this->length_box = (gcnew System::Windows::Forms::TextBox());
			this->Wawelength = (gcnew System::Windows::Forms::GroupBox());
			this->wawelenght_box = (gcnew System::Windows::Forms::TextBox());
			this->Frequency = (gcnew System::Windows::Forms::GroupBox());
			this->frequency_box = (gcnew System::Windows::Forms::TextBox());
			this->Pattern_box = (gcnew System::Windows::Forms::GroupBox());
			this->amplitude_Box = (gcnew System::Windows::Forms::GroupBox());
			this->erad_label = (gcnew System::Windows::Forms::Label());
			this->hphi_label = (gcnew System::Windows::Forms::Label());
			this->etheta_label = (gcnew System::Windows::Forms::Label());
			this->Head_coordinates->SuspendLayout();
			this->Zone->SuspendLayout();
			this->Parameters->SuspendLayout();
			this->Rad->SuspendLayout();
			this->Amperage->SuspendLayout();
			this->Time->SuspendLayout();
			this->Lenght->SuspendLayout();
			this->Wawelength->SuspendLayout();
			this->Frequency->SuspendLayout();
			this->Pattern_box->SuspendLayout();
			this->amplitude_Box->SuspendLayout();
			this->SuspendLayout();
			// 
			// GL_Render_Timer
			// 
			this->GL_Render_Timer->Interval = 10;
			this->GL_Render_Timer->Tick += gcnew System::EventHandler(this, &Dipole_Face::GL_Render_Timer_Tick);
			// 
			// Pattern_Panel
			// 
			this->Pattern_Panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Pattern_Panel->Location = System::Drawing::Point(3, 18);
			this->Pattern_Panel->Name = L"Pattern_Panel";
			this->Pattern_Panel->Size = System::Drawing::Size(1245, 482);
			this->Pattern_Panel->TabIndex = 0;
			this->Pattern_Panel->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Dipole_Face::Pattern_Panel_KeyUp);
			this->Pattern_Panel->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dipole_Face::Pattern_Panel_KeyDown);
			this->Pattern_Panel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Dipole_Face::Pattern_Panel_MouseDown);
			this->Pattern_Panel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Dipole_Face::Pattern_Panel_MouseMove);
			this->Pattern_Panel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Dipole_Face::Pattern_Panel_MouseUp);
			this->Pattern_Panel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Dipole_Face::Pattern_Panel_MouseWheel);
			this->Pattern_Panel->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &Dipole_Face::Pattern_Panel_PreviewKeyDown);
			// 
			// Head_coordinates
			// 
			this->Head_coordinates->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Head_coordinates->BackColor = System::Drawing::Color::Black;
			this->Head_coordinates->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->Head_coordinates->Controls->Add(this->z_location_label);
			this->Head_coordinates->Controls->Add(this->y_location_label);
			this->Head_coordinates->Controls->Add(this->x_location_label);
			this->Head_coordinates->ForeColor = System::Drawing::Color::White;
			this->Head_coordinates->Location = System::Drawing::Point(12, 517);
			this->Head_coordinates->Name = L"Head_coordinates";
			this->Head_coordinates->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->Head_coordinates->Size = System::Drawing::Size(243, 74);
			this->Head_coordinates->TabIndex = 1;
			this->Head_coordinates->TabStop = false;
			this->Head_coordinates->Text = L"Координаты камеры";
			// 
			// z_location_label
			// 
			this->z_location_label->AutoSize = true;
			this->z_location_label->Location = System::Drawing::Point(7, 52);
			this->z_location_label->Name = L"z_location_label";
			this->z_location_label->Size = System::Drawing::Size(25, 17);
			this->z_location_label->TabIndex = 2;
			this->z_location_label->Text = L"Z: ";
			this->z_location_label->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// y_location_label
			// 
			this->y_location_label->AutoSize = true;
			this->y_location_label->Location = System::Drawing::Point(7, 35);
			this->y_location_label->Name = L"y_location_label";
			this->y_location_label->Size = System::Drawing::Size(25, 17);
			this->y_location_label->TabIndex = 1;
			this->y_location_label->Text = L"Y: ";
			this->y_location_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// x_location_label
			// 
			this->x_location_label->AutoSize = true;
			this->x_location_label->Location = System::Drawing::Point(7, 18);
			this->x_location_label->Name = L"x_location_label";
			this->x_location_label->Size = System::Drawing::Size(25, 17);
			this->x_location_label->TabIndex = 0;
			this->x_location_label->Text = L"X: ";
			this->x_location_label->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// scale_label
			// 
			this->scale_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->scale_label->AutoSize = true;
			this->scale_label->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->scale_label->Location = System::Drawing::Point(12, 600);
			this->scale_label->Name = L"scale_label";
			this->scale_label->Size = System::Drawing::Size(78, 19);
			this->scale_label->TabIndex = 2;
			this->scale_label->Text = L"Масштаб: ";
			// 
			// Zone
			// 
			this->Zone->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Zone->Controls->Add(this->Distant_Button);
			this->Zone->Controls->Add(this->Near_Button);
			this->Zone->ForeColor = System::Drawing::Color::White;
			this->Zone->Location = System::Drawing::Point(1268, 8);
			this->Zone->Name = L"Zone";
			this->Zone->Size = System::Drawing::Size(200, 52);
			this->Zone->TabIndex = 3;
			this->Zone->TabStop = false;
			this->Zone->Text = L"Зона";
			// 
			// Distant_Button
			// 
			this->Distant_Button->AutoSize = true;
			this->Distant_Button->Location = System::Drawing::Point(99, 21);
			this->Distant_Button->Name = L"Distant_Button";
			this->Distant_Button->Size = System::Drawing::Size(87, 21);
			this->Distant_Button->TabIndex = 1;
			this->Distant_Button->Text = L"Дальняя";
			this->Distant_Button->UseVisualStyleBackColor = true;
			this->Distant_Button->CheckedChanged += gcnew System::EventHandler(this, &Dipole_Face::Distant_Button_CheckedChanged);
			// 
			// Near_Button
			// 
			this->Near_Button->AutoSize = true;
			this->Near_Button->Checked = true;
			this->Near_Button->Location = System::Drawing::Point(6, 21);
			this->Near_Button->Name = L"Near_Button";
			this->Near_Button->Size = System::Drawing::Size(87, 21);
			this->Near_Button->TabIndex = 0;
			this->Near_Button->TabStop = true;
			this->Near_Button->Text = L"Ближняя";
			this->Near_Button->UseVisualStyleBackColor = true;
			this->Near_Button->CheckedChanged += gcnew System::EventHandler(this, &Dipole_Face::Near_Button_CheckedChanged);
			// 
			// Сalculates_flow
			// 
			this->Сalculates_flow->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Dipole_Face::Сalculates_flow_DoWork);
			// 
			// Change_button
			// 
			this->Change_button->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Change_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->Change_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Change_button->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->Change_button->FlatAppearance->BorderSize = 0;
			this->Change_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
			this->Change_button->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Black;
			this->Change_button->ForeColor = System::Drawing::Color::Black;
			this->Change_button->Location = System::Drawing::Point(3, 410);
			this->Change_button->Name = L"Change_button";
			this->Change_button->Size = System::Drawing::Size(189, 23);
			this->Change_button->TabIndex = 4;
			this->Change_button->TabStop = false;
			this->Change_button->Text = L"Применить";
			this->Change_button->UseVisualStyleBackColor = false;
			this->Change_button->Click += gcnew System::EventHandler(this, &Dipole_Face::Change_button_Click);
			// 
			// amperage_box
			// 
			this->amperage_box->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->amperage_box->Location = System::Drawing::Point(6, 21);
			this->amperage_box->Name = L"amperage_box";
			this->amperage_box->Size = System::Drawing::Size(173, 22);
			this->amperage_box->TabIndex = 5;
			this->amperage_box->TabStop = false;
			this->amperage_box->Text = L"1";
			this->amperage_box->TextChanged += gcnew System::EventHandler(this, &Dipole_Face::amperage_box_TextChanged);
			// 
			// Parameters
			// 
			this->Parameters->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Parameters->Controls->Add(this->Rad);
			this->Parameters->Controls->Add(this->Amperage);
			this->Parameters->Controls->Add(this->Change_button);
			this->Parameters->Controls->Add(this->Time);
			this->Parameters->Controls->Add(this->Lenght);
			this->Parameters->Controls->Add(this->Wawelength);
			this->Parameters->Controls->Add(this->Frequency);
			this->Parameters->ForeColor = System::Drawing::Color::White;
			this->Parameters->Location = System::Drawing::Point(1268, 66);
			this->Parameters->Name = L"Parameters";
			this->Parameters->Size = System::Drawing::Size(200, 445);
			this->Parameters->TabIndex = 6;
			this->Parameters->TabStop = false;
			this->Parameters->Text = L"Параметры";
			// 
			// Rad
			// 
			this->Rad->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Rad->Controls->Add(this->rad_box);
			this->Rad->ForeColor = System::Drawing::Color::White;
			this->Rad->Location = System::Drawing::Point(4, 331);
			this->Rad->Name = L"Rad";
			this->Rad->Size = System::Drawing::Size(188, 70);
			this->Rad->TabIndex = 11;
			this->Rad->TabStop = false;
			this->Rad->Text = L"Расстояние от начала координат (м)";
			// 
			// rad_box
			// 
			this->rad_box->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->rad_box->Location = System::Drawing::Point(6, 38);
			this->rad_box->Name = L"rad_box";
			this->rad_box->Size = System::Drawing::Size(173, 22);
			this->rad_box->TabIndex = 0;
			this->rad_box->TabStop = false;
			this->rad_box->Text = L"1";
			this->rad_box->TextChanged += gcnew System::EventHandler(this, &Dipole_Face::rad_box_TextChanged);
			// 
			// Amperage
			// 
			this->Amperage->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Amperage->Controls->Add(this->amperage_box);
			this->Amperage->ForeColor = System::Drawing::Color::White;
			this->Amperage->Location = System::Drawing::Point(4, 21);
			this->Amperage->Name = L"Amperage";
			this->Amperage->Size = System::Drawing::Size(188, 53);
			this->Amperage->TabIndex = 6;
			this->Amperage->TabStop = false;
			this->Amperage->Text = L"Сила тока (а)";
			// 
			// Time
			// 
			this->Time->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Time->Controls->Add(this->time_box);
			this->Time->ForeColor = System::Drawing::Color::White;
			this->Time->Location = System::Drawing::Point(4, 274);
			this->Time->Name = L"Time";
			this->Time->Size = System::Drawing::Size(188, 53);
			this->Time->TabIndex = 10;
			this->Time->TabStop = false;
			this->Time->Text = L"Время (с)";
			// 
			// time_box
			// 
			this->time_box->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->time_box->Location = System::Drawing::Point(6, 21);
			this->time_box->Name = L"time_box";
			this->time_box->Size = System::Drawing::Size(174, 22);
			this->time_box->TabIndex = 0;
			this->time_box->TabStop = false;
			this->time_box->Text = L"1";
			this->time_box->TextChanged += gcnew System::EventHandler(this, &Dipole_Face::time_box_TextChanged);
			// 
			// Lenght
			// 
			this->Lenght->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Lenght->Controls->Add(this->length_box);
			this->Lenght->ForeColor = System::Drawing::Color::White;
			this->Lenght->Location = System::Drawing::Point(4, 80);
			this->Lenght->Name = L"Lenght";
			this->Lenght->Size = System::Drawing::Size(188, 53);
			this->Lenght->TabIndex = 7;
			this->Lenght->TabStop = false;
			this->Lenght->Text = L"Длина диполя (м)";
			// 
			// length_box
			// 
			this->length_box->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->length_box->Location = System::Drawing::Point(6, 21);
			this->length_box->Name = L"length_box";
			this->length_box->Size = System::Drawing::Size(173, 22);
			this->length_box->TabIndex = 0;
			this->length_box->TabStop = false;
			this->length_box->Text = L"1";
			this->length_box->TextChanged += gcnew System::EventHandler(this, &Dipole_Face::length_box_TextChanged);
			// 
			// Wawelength
			// 
			this->Wawelength->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Wawelength->Controls->Add(this->wawelenght_box);
			this->Wawelength->ForeColor = System::Drawing::Color::White;
			this->Wawelength->Location = System::Drawing::Point(4, 139);
			this->Wawelength->Name = L"Wawelength";
			this->Wawelength->Size = System::Drawing::Size(188, 53);
			this->Wawelength->TabIndex = 8;
			this->Wawelength->TabStop = false;
			this->Wawelength->Text = L"Длина волны (м)";
			// 
			// wawelenght_box
			// 
			this->wawelenght_box->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->wawelenght_box->Location = System::Drawing::Point(6, 21);
			this->wawelenght_box->Name = L"wawelenght_box";
			this->wawelenght_box->Size = System::Drawing::Size(173, 22);
			this->wawelenght_box->TabIndex = 0;
			this->wawelenght_box->TabStop = false;
			this->wawelenght_box->Text = L"1";
			this->wawelenght_box->TextChanged += gcnew System::EventHandler(this, &Dipole_Face::wawelenght_box_TextChanged);
			// 
			// Frequency
			// 
			this->Frequency->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->Frequency->Controls->Add(this->frequency_box);
			this->Frequency->ForeColor = System::Drawing::Color::White;
			this->Frequency->Location = System::Drawing::Point(3, 198);
			this->Frequency->Name = L"Frequency";
			this->Frequency->Size = System::Drawing::Size(188, 70);
			this->Frequency->TabIndex = 9;
			this->Frequency->TabStop = false;
			this->Frequency->Text = L"Циклическая частота (рад/с)";
			// 
			// frequency_box
			// 
			this->frequency_box->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->frequency_box->Location = System::Drawing::Point(6, 38);
			this->frequency_box->Name = L"frequency_box";
			this->frequency_box->Size = System::Drawing::Size(173, 22);
			this->frequency_box->TabIndex = 0;
			this->frequency_box->TabStop = false;
			this->frequency_box->Text = L"1";
			this->frequency_box->TextChanged += gcnew System::EventHandler(this, &Dipole_Face::frequency_box_TextChanged);
			// 
			// Pattern_box
			// 
			this->Pattern_box->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Pattern_box->Controls->Add(this->Pattern_Panel);
			this->Pattern_box->ForeColor = System::Drawing::Color::White;
			this->Pattern_box->Location = System::Drawing::Point(12, 8);
			this->Pattern_box->Name = L"Pattern_box";
			this->Pattern_box->Size = System::Drawing::Size(1251, 503);
			this->Pattern_box->TabIndex = 7;
			this->Pattern_box->TabStop = false;
			this->Pattern_box->Text = L"Диаграмма направленности диполя Герца";
			// 
			// amplitude_Box
			// 
			this->amplitude_Box->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->amplitude_Box->Controls->Add(this->erad_label);
			this->amplitude_Box->Controls->Add(this->hphi_label);
			this->amplitude_Box->Controls->Add(this->etheta_label);
			this->amplitude_Box->ForeColor = System::Drawing::Color::White;
			this->amplitude_Box->Location = System::Drawing::Point(261, 517);
			this->amplitude_Box->Name = L"amplitude_Box";
			this->amplitude_Box->Size = System::Drawing::Size(249, 74);
			this->amplitude_Box->TabIndex = 8;
			this->amplitude_Box->TabStop = false;
			this->amplitude_Box->Text = L"Амплитудные значения векторов";
			// 
			// erad_label
			// 
			this->erad_label->AutoSize = true;
			this->erad_label->Location = System::Drawing::Point(6, 52);
			this->erad_label->Name = L"erad_label";
			this->erad_label->Size = System::Drawing::Size(46, 17);
			this->erad_label->TabIndex = 2;
			this->erad_label->Text = L"Erad: ";
			// 
			// hphi_label
			// 
			this->hphi_label->AutoSize = true;
			this->hphi_label->Location = System::Drawing::Point(6, 35);
			this->hphi_label->Name = L"hphi_label";
			this->hphi_label->Size = System::Drawing::Size(45, 17);
			this->hphi_label->TabIndex = 1;
			this->hphi_label->Text = L"Hphi: ";
			// 
			// etheta_label
			// 
			this->etheta_label->AutoSize = true;
			this->etheta_label->Location = System::Drawing::Point(6, 18);
			this->etheta_label->Name = L"etheta_label";
			this->etheta_label->Size = System::Drawing::Size(57, 17);
			this->etheta_label->TabIndex = 0;
			this->etheta_label->Text = L"Etheta: ";
			// 
			// Dipole_Face
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(1476, 628);
			this->Controls->Add(this->amplitude_Box);
			this->Controls->Add(this->Pattern_box);
			this->Controls->Add(this->Parameters);
			this->Controls->Add(this->Zone);
			this->Controls->Add(this->scale_label);
			this->Controls->Add(this->Head_coordinates);
			this->ForeColor = System::Drawing::Color::White;
			this->Name = L"Dipole_Face";
			this->ShowIcon = false;
			this->Text = L"Модель Диполя";
			this->Load += gcnew System::EventHandler(this, &Dipole_Face::Dipole_Face_Load);
			this->SizeChanged += gcnew System::EventHandler(this, &Dipole_Face::Dipole_Face_SizeChanged);
			this->Head_coordinates->ResumeLayout(false);
			this->Head_coordinates->PerformLayout();
			this->Zone->ResumeLayout(false);
			this->Zone->PerformLayout();
			this->Parameters->ResumeLayout(false);
			this->Rad->ResumeLayout(false);
			this->Rad->PerformLayout();
			this->Amperage->ResumeLayout(false);
			this->Amperage->PerformLayout();
			this->Time->ResumeLayout(false);
			this->Time->PerformLayout();
			this->Lenght->ResumeLayout(false);
			this->Lenght->PerformLayout();
			this->Wawelength->ResumeLayout(false);
			this->Wawelength->PerformLayout();
			this->Frequency->ResumeLayout(false);
			this->Frequency->PerformLayout();
			this->Pattern_box->ResumeLayout(false);
			this->amplitude_Box->ResumeLayout(false);
			this->amplitude_Box->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::String^ Point_To_Comma(System::String ^ text){
		System::String^ result = L"";
		for (int i = 0; i < text->Length; i++)
			if (text[i] != L'.')
				result += text[i];
			else
				result += L',';
		return result;
	}

	private: System::Void Disable_Interface(){
		disable(Near_Button)
		disable(Distant_Button)
		disable(Change_button)
		active = false;
		status = false;
	}
	private: System::Void Enable_Interface(){
		enable(Near_Button)
		enable(Distant_Button)
		status = true;
	}

	private: System::Void Show_Exhaust()
	{
		if (Near_Button->Checked)
		{
			set_text_back(etheta_label, "Etheta: ", dr->Get_Amplitude_Etheta()," В/м");
			set_text_back(erad_label, "Erad: ", dr->Get_Amplitude_Erad()," В/м");
			set_text_back(hphi_label, "Hphi: ", dr->Get_Amplitude_Hphi(), " Тл");
		}
		else
		{
			set_text_back(etheta_label, "Etheta: ", dr->Get_Amplitude_Etheta(), " В/м");
			set_text_back(erad_label, "Erad: ", 0, " В/м");
			set_text_back(hphi_label, "Hphi: ", dr->Get_Amplitude_Hphi(), " Тл");
		}

	}
	private: System::Void Dipole_Face_Load(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		System::Drawing::Size^ s = Pattern_Panel->Size;
		gl->Start_GL((HWND)Pattern_Panel->Handle.ToPointer(), s->Width, s->Height);
		active = true;
		set_text(x_location_label, L"X: ", gl->Get_x_Location());
		set_text(y_location_label, L"Y: ", gl->Get_y_Location());
		set_text(z_location_label, L"Z: ", gl->Get_z_Location());
		set_text(scale_label, L"Масштаб: ", gl->Get_Scale());
		Disable_Interface();
		Сalculates_flow->RunWorkerAsync();
		GL_Render_Timer->Start();
	}
	private: System::Void GL_Render_Timer_Tick(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		if (active)
		{
			if (!status)
			{
				Enable_Interface();
				Show_Exhaust();
			}
			bool result = true;
			for (unsigned int i = 0; i < parameters.size(); i++)
				if (!parameters[i])
				{
					result = false;
					break;
				}
			if (result)
				enable(Change_button)
			else
				disable(Change_button)
			try
			{
				gl->Draw_GL_Scene(electic_field_line, magnetic_field_line, Etheta_vector, Hphi_vector);
			}
			catch (...)
			{

			}
		}
	}
	private: System::Void Dipole_Face_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		if (active)
		{
			System::Drawing::Size^ s = Pattern_Panel->Size;
			gl->Resize_GL_Scene(s->Width, s->Height);
		}
	}

	private: System::Void Pattern_Panel_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
		if (active)
		{
			switch (e->KeyCode)
			{
			case Keys::Down:
				e->IsInputKey = true;
				gl->Set_y_Location(gl->Get_y_Location() - 1);
				set_text(y_location_label, L"Y: ", gl->Get_y_Location());
				break;
			case Keys::Up:
				e->IsInputKey = true;
				gl->Set_y_Location(gl->Get_y_Location() + 1);
				set_text(y_location_label, L"Y: ", gl->Get_y_Location());
				break;
			case Keys::Left:
				e->IsInputKey = true;
				gl->Set_x_Location(gl->Get_x_Location() - 1);
				set_text(x_location_label, L"X: ", gl->Get_x_Location());
				break;
			case Keys::Right:
				e->IsInputKey = true;
				gl->Set_x_Location(gl->Get_x_Location() + 1);
				set_text(x_location_label, L"X: ", gl->Get_x_Location());
				break;
			}
		}
	}
	private: System::Void Pattern_Panel_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (active)
		{
			if (shift)
			{
				gl->Set_Scale(gl->Get_Scale() + (e->Delta * SystemInformation::MouseWheelScrollLines) / 3600.0);
				set_text(scale_label, L"Масштаб: ", gl->Get_Scale());
			}
			else
			{
				gl->Set_z_Location(gl->Get_z_Location() + e->Delta * SystemInformation::MouseWheelScrollLines / 360);
				set_text(z_location_label, L"Z: ", gl->Get_z_Location());
			}
		}
	}
	private: System::Void Pattern_Panel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		release(e, sender);
		if (active)
			rotation = true;
		else
			rotation = false;
	}
	private: System::Void Pattern_Panel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		release(e, sender);
		if (active)
			rotation = false;
		else
			rotation = false;
	}
	private: System::Void Pattern_Panel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		Pattern_Panel->Focus();
		if (rotation)
			gl->Alter_Angle(std::pair<GLint, GLint>(MouseXY->x, e->X), std::pair<GLint, GLint>(MouseXY->y, e->Y));
		MouseXY->x = e->X;
		MouseXY->y = e->Y;
	}
	private: System::Void Pattern_Panel_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (active)
			if (e->KeyCode == Keys::ShiftKey)
				shift = false;
	}
	private: System::Void Pattern_Panel_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (active)
			if (e->KeyCode == Keys::ShiftKey)
				shift = true;
	}

	private: System::Void Near_Button_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		if (active)
		{
			try
			{
				Disable_Interface();
				Сalculates_flow->RunWorkerAsync();
			}
			catch (...)
			{
			
			}
		}
	}
	private: System::Void Distant_Button_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		if (active)
		{
			try
			{
				Disable_Interface();
				Сalculates_flow->RunWorkerAsync();
			}
			catch (...)
			{
			
			}
		}
	}

	private: System::Void Сalculates_flow_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		release(e, sender);
		try
		{
			electic_field_line.clear();
			magnetic_field_line.clear();
			dr->Get_Radiation_Pattern(!Near_Button->Checked, electic_field_line, magnetic_field_line);
			Etheta_vector = dr->Get_Etheta_Vector(!Near_Button->Checked);
			Hphi_vector = dr->Get_Hphi_Vector(!Near_Button->Checked);
		}
		catch (...)
		{

		}
		active = true;
	}

	private: System::Void check(System::Windows::Forms::TextBox^ textBox, unsigned int number)
	{
		try
		{
			System::Convert::ToDouble(Point_To_Comma(textBox->Text));
			if (!parameters[number])
			{
				parameters[number] = true;
				textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			}
		}
		catch (...)
		{
			if (parameters[number])
			{
				parameters[number] = false;
				textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			}
		}
	}
	private: System::Void amperage_box_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		check(amperage_box, 0);
	}
	private: System::Void length_box_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		check(length_box, 1);
	}
	private: System::Void wawelenght_box_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		check(wawelenght_box, 2);
	}
	private: System::Void frequency_box_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		check(frequency_box, 3);
	}
	private: System::Void time_box_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		check(time_box, 4);
	}
	private: System::Void rad_box_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		check(rad_box, 5);
	}
	private: System::Void Change_button_Click(System::Object^  sender, System::EventArgs^  e) {
		release(e, sender);
		Disable_Interface();
		try
		{
			dr->Set_Parameters(System::Convert::ToDouble(Point_To_Comma(length_box->Text)),
				System::Convert::ToDouble(Point_To_Comma(amperage_box->Text)),
				System::Convert::ToDouble(Point_To_Comma(wawelenght_box->Text)),
				System::Convert::ToDouble(Point_To_Comma(frequency_box->Text)),
				System::Convert::ToDouble(Point_To_Comma(time_box->Text)),
				System::Convert::ToDouble(Point_To_Comma(rad_box->Text))
			);
		}
		catch (...)
		{
			MessageBox::Show("Bad values!");
		}
		Сalculates_flow->RunWorkerAsync();
	}
};
}
