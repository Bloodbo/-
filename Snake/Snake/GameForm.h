#pragma once

#include <time.h>
#include <stdlib.h>

namespace Snake {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// —водка дл€ GameForm
	/// </summary>
	public ref class GameForm : public System::Windows::Forms::Form
	{
	public:
		GameForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~GameForm()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void OnPaint(System::Object^ obj, PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;

			Brush^ snakeBrush = gcnew SolidBrush(Color::Black); // кисть
			for each(Point el in snake)
			    g->FillRectangle(snakeBrush, el.X, el.Y, blockSize, blockSize);
			Brush^ fruitBrush = gcnew SolidBrush(Color::Red); // создали цвета дл€ змеи и фруктов
			g->FillRectangle(fruitBrush, fruitPosition.X, fruitPosition.Y, blockSize, blockSize);
		}

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
		List<Point>^ snake;
		Point snakePosition; // создание объекта змеи и фрукта
		Point fruitPosition;
		const int blockSize = 20; // базовые размеры в игре 
		int fruitCount = 0;
		Label^ scoreLabel;

		Timer^ timer; // поле
		int moveX = blockSize, moveY = 0;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->KeyPreview = true;
			this->Focus();
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(400, 400);
			this->Text = L"SnakeGame";
			this->BackColor = Color::Green;
			this->ResumeLayout(false);

			scoreLabel = gcnew Label();
			scoreLabel->ForeColor = Color::White;
			scoreLabel->BackColor = Color::Transparent;
			scoreLabel->Text = "Score: 0";
			scoreLabel->Location = Point(10, 10);
			this->Controls->Add(scoreLabel);

			snake = gcnew List<Point>(); 
			snake->Add(Point(100,100));
			srand(time(NULL));
			PlaceFruit();

			timer = gcnew Timer(); // выделение пам€ти
			timer->Interval = 100;
			timer->Tick += gcnew EventHandler(this, &GameForm::OnTimerTick);
			timer->Start(); // Start the timer here

			this->Paint += gcnew PaintEventHandler(this, &GameForm::OnPaint);
			this->KeyDown += gcnew KeyEventHandler(this, &GameForm::OnKeyDown);
		}
#pragma endregion
		void PlaceFruit() {
			int maxX = this->ClientSize.Width / blockSize; // сколько квадратов можно получить по высоте и ширине нашей проге
			int maxY = this->ClientSize.Height / blockSize;

			do {
				fruitPosition = Point(rand() % maxX * blockSize, rand() % maxY * blockSize); // *blocksize чтобы привести в пиксельную систему стандартную
			} while (snake->Contains(fruitPosition));
		}

		void OnTimerTick(Object^ obj, EventArgs^ e) {
			MoveSnake();

			if (snake[0].X < 0 || snake[0].Y < 0 || snake[0].X >= this->ClientSize.Width || snake[0].Y >= this-> ClientSize.Height) {
				timer->Stop();
				MessageBox::Show("Game Over");
				return;
			}

			if (snake->Count >= 4) { //проверка на самосъедание
				for (int i = 1; i < snake->Count; i++) {  // цикл идЄт до кол-во элементов в нашем списке
					if (snake[0] == snake[i]) {
						timer->Stop();
						MessageBox::Show("Game Over. You ate yourself ! ! ! ");
						return;
					}
				}
			}
			
			if (snake[0] == fruitPosition) {
				fruitCount++;
				scoreLabel->Text = "Score: " + fruitCount.ToString(); // привод к формату строки 
				GrowthSnake(); //увелечение питона
				PlaceFruit();
			}

			this->Invalidate();
		}

		void MoveSnake() {
			Point newHead = snake[0];

			newHead.X += moveX;
			newHead.Y += moveY;
			snake->Insert(0, newHead); // перестановка 
			snake->RemoveAt(snake->Count - 1);
		}

		void GrowthSnake() {
			Point newHead = snake[0];

			newHead.X += moveX;
			newHead.Y += moveY;
			snake->Insert(0, newHead);
		}

		void OnKeyDown(Object^ obj, KeyEventArgs^ e) {
			switch (e->KeyCode)
			{
			case Keys::Up:
				if (moveY == 0) {
					moveX = 0;
					moveY = -blockSize;
				}
				break;
			case Keys::Down:
				if (moveY == 0) {
					moveX = 0;
					moveY = blockSize;
				}
				break;
			case Keys::Left:
				if (moveX == 0) {
					moveX = -blockSize;
					moveY = 0;
				}
				break;
			case Keys::Right:
				if (moveX == 0) {
					moveX = blockSize;
					moveY = 0;
				}
				break;
			case Keys::P:
				MessageBox::Show(" лавиша P нажата");
				timer->Enabled = !timer->Enabled;
				this->Text = timer->Enabled ? L"SnakeGame" : L"SnakeGame - ѕауза";
				break;

			}
		}

		}
	};
}
