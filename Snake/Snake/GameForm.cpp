#include "GameForm.h"
using namespace System;
using namespace System::Windows::Forms; 
 

[STAThreadAttribute] // аннотация
int main(array<String^>^ args) { //работа с динамической памятью для array и string
	Application::SetCompatibleTextRenderingDefault(false); //откл работа с текстом по умолчанию
	Application::EnableVisualStyles(); // вкл различные визуальные стили
	Snake::GameForm form; // создание объекта - основное окно
	Application::Run(% form); // правильная передача объекта ссылочного класса

}