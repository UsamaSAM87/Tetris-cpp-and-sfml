#include "Piece.h"

int Random(int min, int max)
{
	int num = 0;
	for (int i = 0; i < 1; i++)
	{
		num = (rand() % (max - min + 1)) + min;
	}
	return num;
}

/* creates shapes in 3d array 2 dimensions 4 by 6 store 1
piece and here we should need to use 7 piece thats why first dimension is 7*/

int arrangements[7][4][6] =
{
		{{0, 4, 1, 2, 0, 0}, {0, 4, 1, 2, 0, 0}, {0, 4, 1, 2, 0, 0}, {0, 4, 1, 2, 0, 0}},
		{{1, 0, 3, 3, 0, 0}, {0, 2, 0, 4, 4, 0}, {0, 1, 0, 3, 3, 0}, {0, 0, 2, 0, 4, 4}},
		{{0, 3, 2, 0, 1, 0}, {0, 4, 0, 2, 1, 0}, {0, 3, 0, 1, 4, 0}, {0, 2, 0, 4, 3, 0}},
		{{0, 3, 0, 1, 2, 0}, {0, 2, 0, 4, 1, 0}, {0, 1, 0, 3, 4, 0}, {0, 4, 0, 2, 3, 0}},
		{{0, 3, 0, 2, 1, 0}, {0, 2, 0, 1, 4, 0}, {0, 1, 0, 4, 3, 0}, {0, 4, 0, 3, 2, 0}},
		{{0, 1, 0, 2, 0, 3}, {0, 1, 0, 2, 0, 4}, {0, 1, 0, 3, 0, 4}, {0, 2, 0, 3, 0, 4}},
		{{0, 1, 0, 2, 3, 0}, {0, 4, 0, 1, 2, 0}, {0, 3, 0, 4, 1, 0}, {0, 2, 0, 3, 4, 0}}
};

int PieceNo = 0, FormationNo = 0;

int a[6] = { 0, 0, 0, 0, 0, 0 };

class Board : public Piece
{
public:
	box** board;
	Piece CurrentPiece;

	// make 2d array of board
	Board()
	{
		board = new box * [30];
		for (int i = 0; i < 30; i++)
		{
			board[i] = new box[17];
		}
		for (int i = 0; i < 29; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				board[i][j].SetDown(&board[i + 1][j]), board[i + 1][j].SetUp(&board[i][j]);
			}
		}
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				board[i][j].SetRight(&board[i][j + 1]), board[i][j + 1].SetLeft(&board[i][j]);
			}
		}
	}
	//check is piece touch the bottom line or not
	bool LineDetected()
	{
		bool detect = true;
		for (int i = 29; i >= 0; i--)
		{
			detect = 1;
			for (int j = 0; j < 17; j++)
			{
				if (board[i][j].GetBoxColor() == 0)
				{
					detect = false;
					break;
				}
			}
			if (detect)
				Rearrange(i);
		}
		return detect;
	}
	//generate random piece one by one in 2d array
	bool GeneratePiece()
	{
		srand(time(0));
		bool val = false;
		box* b = GetCoordinateBox(1, 8);
		if (b->GetBoxColor() == 0)
		{
			PieceNo = Random(0, 6), FormationNo = Random(0, 3);
			for (int k = 0; k < 6; k++)
			{
				a[k] = arrangements[PieceNo][FormationNo][k];
			}
			CurrentPiece.SetData(b, Random(0, 7), a);
			val = this->CurrentPiece.VerifyPath();
			if (val)
			{
				CurrentPiece.CreatPiece();
			}
		}
		b = nullptr;
		return val;
	}
	//rotate the shape of 2d int shape of piece and display on board
	void Rotate()
	{
		CurrentPiece.ClearPiece();
		int prev[6]{ 0 };
		for (int k = 0; k < 6; k++)
		{
			prev[k] = a[k];
		}
		FormationNo++;
		if (FormationNo >= 4)
		{
			FormationNo = 0;
		}
		for (int k = 0; k < 6; k++)
		{
			a[k] = arrangements[PieceNo][FormationNo][k];
		}
		CurrentPiece.SetDirections(a);
		if (!this->CurrentPiece.VerifyPath())
			for (int k = 0; k < 6; k++)
			{
				a[k] = prev[k];
			}
		CurrentPiece.SetDirections(a);
		CurrentPiece.CreatPiece();
	}

	//rearrange the shape of 2d array by taking the transpose tec
	void Rearrange(int row)
	{
		for (int j = 0; j < 17; j++)
		{
			board[row][j].SetBoxColor(0);
		}
		for (int i = row; i > 0; i--)
		{
			for (int j = 0; j < 17; j++)
			{
				board[i][j].SetBoxColor(board[i - 1][j].GetBoxColor());
			}
		}
		for (int j = 0; j < 17; j++)
		{
			board[0][j].SetBoxColor(0);
		}
	}

	//when user press down key it basically check that can we move downward or not etc
	bool Gravity()
	{
		bool val = false;
		this->CurrentPiece.ClearPiece();
		if (this->CurrentPiece.GetStartBox()->GetDown() != nullptr)
		{
			this->CurrentPiece.SetStartBox(this->CurrentPiece.GetStartBox()->GetDown()); val = true;
			if (!this->CurrentPiece.VerifyPath())
			{
				this->CurrentPiece.SetStartBox(this->CurrentPiece.GetStartBox()->GetUp()); val = false;
			}
		}
		this->CurrentPiece.CreatPiece();
		return val;
	}
	//check is box can move right by checking that is right space empty 
	void MoveRight()
	{
		this->CurrentPiece.ClearPiece();
		if (this->CurrentPiece.GetStartBox()->GetRight())
		{
			this->CurrentPiece.SetStartBox(this->CurrentPiece.GetStartBox()->GetRight());
			if (!this->CurrentPiece.VerifyPath())
			{
				this->CurrentPiece.SetStartBox(this->CurrentPiece.GetStartBox()->GetLeft());
			}
		}
		this->CurrentPiece.CreatPiece();
	}
	//move box of piece right when user press right key by checking is right of that piece is empty or not
	void MoveLeft()
	{
		this->CurrentPiece.ClearPiece();
		if (this->CurrentPiece.GetStartBox()->GetLeft())
		{
			this->CurrentPiece.SetStartBox(this->CurrentPiece.GetStartBox()->GetLeft());
			if (!this->CurrentPiece.VerifyPath())
			{
				this->CurrentPiece.SetStartBox(this->CurrentPiece.GetStartBox()->GetRight());
			}
		}
		this->CurrentPiece.CreatPiece();
	}
	//clears the board
	void ClearBoard()
	{
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				board[i][j].SetBoxColor(0);
			}
		}
	}
	//get the cordinates of piece box
	box* GetCoordinateBox(int row, int col)
	{
		return &board[row][col];
	};
	//print 2d array or box or we can say grid that store actual data
	void PrintBoard()
	{
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				std::cout << board[i][j].GetBoxColor() << ' ';
			}
			std::cout << '\n';
		}
		std::cout << std::endl;
	}

	void  print() override
	{
		std::cout << "CurrentPieceColor: "; CurrentPiece.print(); std::cout << "\n";
	}

	~Board()
	{
		for (int i = 0; i < 30; i++)
			delete[] board[i], board[i] = nullptr;
		delete[] board, board = nullptr;
	}
};