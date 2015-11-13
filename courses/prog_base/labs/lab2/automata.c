#define NOTHING -100
enum Ops { POP = -4, CONTINUE, REPEAT, BREAK };
struct Move
{
	enum Ops m;
	int state;
};

int run(int moves[], int movesLen, int res1[], int resLen)
{
int resPos = 0;
	int movePos = 0;
	int i;
	int curStance = 0;
	struct Move mov[4][4];
	mov[0][0].m = 12;
	mov[0][0].state = 1;
	mov[0][1].m = CONTINUE;
	mov[0][1].state= 1;
	mov[0][2].m = 13;
	mov[0][2].state = 2;
	mov[0][3].m = BREAK;
	mov[0][3].state = NOTHING;
	mov[1][0].m = NOTHING;
	mov[1][0].state = NOTHING;
	mov[1][1].m = CONTINUE;
	mov[1][1].state = 2;
	mov[1][2].m = 14;
	mov[1][2].state = 3;
	mov[1][3].m = POP;
	mov[1][3].state = 2;
	mov[2][0].m = POP;
	mov[2][0].state = 3;
	mov[2][1].m = CONTINUE;
	mov[2][1].state = 3;
	mov[2][2].m = POP;
	mov[2][2].state = 0;
	mov[2][3].m = 15;
	mov[2][3].state = 1;
	mov[3][0].m = 18;
	mov[3][0].state = 0;
	mov[3][1].m = CONTINUE;
	mov[3][1].state = 0;
	mov[3][2].m = 16;
	mov[3][2].state = 2;
	mov[3][3].m = REPEAT;
	mov[3][3].state = 1;


for (i = 0; i < movesLen; i++)
	{
if (!move(res1, resLen, &resPos, mov, moves[i], &curStance))
		{
			int n;
			for (n = resPos; n < resLen; n++)
				res1[n] = 0;
			return resPos;
		}
	}
	return resPos;
}
int move(int res1[], int resLen, int * resPos, struct Move mov[4][4], int moveNum, int * curStance)
{
	struct Move currMov;
	switch (moveNum)
	{
		case 9:
		{
			currMov = mov[*curStance][0];
			*curStance = currMov.state;
		}
		break;
		case 17:
		{
			currMov = mov[*curStance][1];
			*curStance = currMov.state;
		}
		break;
		case 27:
		{
			currMov = mov[*curStance][2];
			*curStance = currMov.state;
		}
		break;
		case 207:
		{
			currMov = mov[*curStance][3];
			*curStance = currMov.state;
		}
		break;
		default:
		{
			return 0;
		}
	}
	switch (currMov.m)
	{
		case POP:
		{
		    if(*resPos>0){
                (*resPos)--;}
            else{
                return 0;}
		}
		break;
		case CONTINUE:
		{
			return 1;
		}
		break;
		case REPEAT:
		{
			move(res1, resLen, resPos, mov, moveNum, curStance);
		}
		break;
		case BREAK:
		{
			return 0;
		}
		break;
		case NOTHING:
		{
			return 0;
		}
		default:
		{

			res1[*resPos] = currMov.m;
			if(*resPos<resLen)
                (*resPos)++;
            else
                return 0;
		}
	}
}



