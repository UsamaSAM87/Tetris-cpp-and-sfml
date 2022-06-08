#include <iostream>

class box
{
private:
	int BoxColor;
	box* Right, * Left, * Up, * Down;
public:
	/* set box colour,  cordinates margin from top left right and bottom and
	take an array and make a piece for visibile on the screen*/
	box(int color = 0, box* rbox = nullptr, box* lbox = nullptr, box* ubox = nullptr, box* dbox = nullptr)
	{
		BoxColor = color, Right = nullptr, Left = nullptr, Up = nullptr, Down = nullptr;
		if (rbox)
		{
			Right = rbox;
		}
		if (lbox)
		{
			Left = lbox;
		}
		if (ubox)
		{
			Up = ubox;
		}
		if (dbox)
		{
			Down = dbox;
		}
	}

	//copy constructor that copies object of box when we return A box with out by reference
	box(const box& obj)
	{
		BoxColor = 0, Right = nullptr, Left = nullptr, Up = nullptr, Down = nullptr;
		BoxColor = obj.GetBoxColor(), Right = obj.GetRight(), Left = obj.GetLeft(), Up = obj.GetUp(), Down = obj.GetDown();
	}

	box& operator=(const box& obj)
	{
		BoxColor = 0, Right = nullptr, Left = nullptr, Up = nullptr, Down = nullptr;
		BoxColor = obj.GetBoxColor(), Right = obj.GetRight(), Left = obj.GetLeft(), Up = obj.GetUp(), Down = obj.GetDown();
		return *this;
	}


	//getters function that return colour of the box and margin from left right and from top 
	int GetBoxColor() const
	{
		return this->BoxColor;
	};

	box* GetRight() const
	{
		return this->Right;
	};

	box* GetLeft() const
	{
		return this->Left;
	};

	box* GetUp() const
	{
		return this->Up;
	};

	box* GetDown() const
	{
		return this->Down;
	};

	//setter function that set the box colour margin from left right fro. Top and from bottom 

	void SetBoxColor(int c)
	{
		this->BoxColor = c;
	};

	void SetRight(box* ptrbox)
	{
		this->Right = ptrbox;
	};

	void SetLeft(box* ptrbox)
	{
		this->Left = ptrbox;
	};

	void SetUp(box* ptrbox)
	{
		this->Up = ptrbox;
	};

	void SetDown(box* ptrbox)
	{
		this->Down = ptrbox;
	};
	/*Virtual print function*/
	void virtual print()
	{
		std::cout << "BoxColor: " << this->BoxColor << "\n";
	}

	~box()
	{
		BoxColor = 0, Right = nullptr, Left = nullptr, Up = nullptr, Down = nullptr;
	}
};
