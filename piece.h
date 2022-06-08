#include "Box.h"

class Piece : public box
{
private:
	box* startBox;
	int PieceColor;
	int* directions;

public:
	/* it will creqt a box that represent a shape it takes a box,
	colour for that box and array of piece and make a colour piece */
	Piece(box* Sbox = nullptr, int const Pcolor = 0, const int* arr = nullptr)
	{
		this->startBox = nullptr, this->PieceColor = 0, this->directions = new int[6]{ 0 };
		if (Pcolor != 0)
		{
			PieceColor = Pcolor;
		}
		if (Sbox)
		{
			startBox = Sbox;
		}
		if (arr)
		{
			for (int i = 0; i < 6; i++)
			{
				directions[i] = arr[i];
			}
		}
	}
	//verify path it basically check that is piece can move down 
	bool VerifyPath()
	{
		box* ref = this->startBox;
		for (int i = 0; i < 6; i++)
		{
			if (directions[i] == 0 && ref->GetBoxColor() == 0)
			{
				ref = startBox;
			}
			else if (directions[i] == 0 && ref->GetBoxColor() != 0)
			{
				ref = nullptr;	return false;
			}
			else if (directions[i] == 1 && ref->GetRight() && ref->GetRight()->GetBoxColor() == 0)
			{
				ref = ref->GetRight();
			}
			else if (directions[i] == 1 && (!ref->GetRight() || ref->GetRight()->GetBoxColor() != 0))
			{
				ref = nullptr;	return false;
			}
			else if (directions[i] == 2 && ref->GetUp() && ref->GetUp()->GetBoxColor() == 0)
			{
				ref = ref->GetUp();
			}
			else if (directions[i] == 2 && (!ref->GetUp() || ref->GetUp()->GetBoxColor() != 0))
			{
				ref = nullptr;	return false;
			}
			else if (directions[i] == 3 && ref->GetLeft() && ref->GetLeft()->GetBoxColor() == 0)
			{
				ref = ref->GetLeft();
			}
			else if (directions[i] == 3 && (!ref->GetLeft() || ref->GetLeft()->GetBoxColor() != 0))
			{
				ref = nullptr;	return false;
			}
			else if (directions[i] == 4 && ref->GetDown() && ref->GetDown()->GetBoxColor() == 0)
			{
				ref = ref->GetDown();
			}
			else if (directions[i] == 4 && (!ref->GetDown() || ref->GetDown()->GetBoxColor() != 0))
			{
				ref = nullptr;	return false;
			}
		}
		ref = nullptr;
		return true;
	}

	//Creat a piece the next time bcz constructor will generate piece only once
	void CreatPiece()
	{
		box* ref = this->startBox;
		for (int i = 0; i < 6; i++)
		{
			if (directions[i] == 0)
			{
				ref = startBox;
			}
			else if (directions[i] == 1 && ref->GetRight())
			{
				ref = ref->GetRight();
			}
			else if (directions[i] == 2 && ref->GetUp())
			{
				ref = ref->GetUp();
			}
			else if (directions[i] == 3 && ref->GetLeft())
			{
				ref = ref->GetLeft();
			}
			else if (directions[i] == 4 && ref->GetDown())
			{
				ref = ref->GetDown();
			}
			ref->SetBoxColor(PieceColor);
		}
		ref = nullptr;
	}

	/*if we place a piece in 2d array and now our task is to move down 1 index
	and move left and right 1 index then before performing this task
	we will call this function it will clear the peice in 2d array*/
	void ClearPiece()
	{
		box* ref = this->startBox;
		for (int i = 0; i < 6; i++)
		{
			if (directions[i] == 0)
			{
				ref = startBox;
			}
			else if (directions[i] == 1 && ref->GetRight())
			{
				ref = ref->GetRight();
			}
			else if (directions[i] == 2 && ref->GetUp())
			{
				ref = ref->GetUp();
			}
			else if (directions[i] == 3 && ref->GetLeft())
			{
				ref = ref->GetLeft();
			}
			else if (directions[i] == 4 && ref->GetDown())
			{
				ref = ref->GetDown();
			}
			ref->SetBoxColor(0);
		}
		ref = nullptr;
	}

	//get box started value
	box* GetStartBox()
	{
		return this->startBox;
	};

	//started value in the box for draw a piece 
	void SetStartBox(box* sBox)
	{
		this->startBox = sBox;
	};

	// this function will call when we change the direction of the piece to set or create that type of piece on screen	
	void SetData(box* Sbox, int const Pcolor, const int* arr)
	{
		this->startBox = nullptr, this->PieceColor = 0, this->directions = new int[6]{ 0 };
		PieceColor = Pcolor;
		if (Sbox)
		{
			startBox = Sbox;
		}
		if (arr)
		{
			for (int i = 0; i < 6; i++)
			{
				directions[i] = arr[i];
			}
		}
	}

	//this function will set the direction of piece but not property on the screen for example shape colour etc
	void SetDirections(int* dir)
	{
		for (int i = 0; i < 6; i++)
		{
			directions[i] = dir[i];
		}
	};

	~Piece()
	{
		this->startBox = nullptr, this->PieceColor = 0;
		delete[] directions, directions = nullptr;
	}
};
