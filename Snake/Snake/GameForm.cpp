#include "GameForm.h"
using namespace System;
using namespace System::Windows::Forms; 
 

[STAThreadAttribute] // ���������
int main(array<String^>^ args) { //������ � ������������ ������� ��� array � string
	Application::SetCompatibleTextRenderingDefault(false); //���� ������ � ������� �� ���������
	Application::EnableVisualStyles(); // ��� ��������� ���������� �����
	Snake::GameForm form; // �������� ������� - �������� ����
	Application::Run(% form); // ���������� �������� ������� ���������� ������

}