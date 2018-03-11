#include <stdio.h>
#include <unistd.h>

typedef struct box {
	int entry;
	int original;
}box;

int place(box sudoku[9][9],int row,int col,int newentry) {
	for(int j=0;j<9;j++) {
		if(sudoku[row][j].entry==newentry) {
			return 0;
		}
	}
	int brow=(row/3)*3+1,bcol=(col/3)*3+1;
	for(int i=-1;i<=1;i++) {
		for(int j=-1;j<=1;j++) {
			if(sudoku[i+brow][j+bcol].entry==newentry) {
				return 0;
			}
		}
	}
	for(int i=0;i<9;i++) {
		if(sudoku[i][col].entry==newentry) {
			return 0;
		}
	}
	return 1;
}

void print_sudoku(box sudoku[9][9]) {
	// usleep(500);
	// printf("\033[2J");
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			printf("%-2d",sudoku[i][j].entry);
		}
		printf("\n");
	}
}

int solve_sudoku(box sudoku[9][9],int row,int col) {
	if(row==9) {
		return 1;
	}
	// print_sudoku(sudoku);
	int nextrow=(col==8?(row+1):row);
	int nextcol=(col+1)%9;
	if(sudoku[row][col].original) {
		return solve_sudoku(sudoku,nextrow,nextcol);
	}
	for(int s=1;s<=9;s++) {
		if(place(sudoku,row,col,s)&&(sudoku[row][col].entry=s,solve_sudoku(sudoku,nextrow,nextcol))) {
			return 1;
		}
	}
	sudoku[row][col].entry=0;
	return 0;
}

int main() {
	box sudoku[9][9]={0};
	FILE *input=fopen("input.txt","r");
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			fscanf(input,"%d",&sudoku[i][j].entry);
			if(sudoku[i][j].entry) {
				sudoku[i][j].original=1;
			}
		}
	}
	fclose(input);
	if(solve_sudoku(sudoku,0,0)) {
		// printf("\033[2J");
		FILE *output=fopen("output.txt","w");
		for(int i=0;i<9;i++) {
			for(int j=0;j<9;j++) {
				fprintf(output,"%-2d",sudoku[i][j].entry);
				printf("%-2d",sudoku[i][j].entry);
			}
			fprintf(output,"\n");
			printf("\n");
		}
		fclose(output);
	}
	return 0;
}