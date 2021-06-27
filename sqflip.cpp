
Skip to content
Pull requests
Issues
Marketplace
Explore
@proton-cell
proton-cell /
Square-Flip

1
1

    0

Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights

    Settings

Square-Flip/Square.txt
@proton-cell
proton-cell first commit
Latest commit 3e087ec 6 hours ago
History
1 contributor
157 lines (130 sloc) 4.03 KB
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<stdio.h> 

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400
#define SPACEBAR 32

using namespace std;

// Global Variables
char option, txtScore[5];
int score = 1; 
	
void GameOver(){
	cleardevice(); // clear screen
	
	// Print Game Over Text
	settextstyle(4,0,9);
	outtextxy(300,300,"Game Over");

	settextstyle(4,0,2);
	outtextxy(500,420,"Press any key to quit...");
	getch();
	score = 0; // reset score
}
void DrawTriangleUp(int x1, int y1, int x2, int y2){
	fillpoly(4, new int[8]{x1, y2, x2, y2, (x1+x2)/2, y1, x1, y2} );
}
void DrawTriangleDown(int x1, int y1, int x2, int y2){
	fillpoly(4, new int[8]{x1, y1, x2, y1, (x1+x2)/2, y2, x1, y1} );
}

int main(){
	srand((unsigned) time(0));
		
	int gd = DETECT, gm, err, tmp;
	initgraph( & gd, & gm, "C:\\tc\\bgi");
    
	// Enemy Variables
	// Enemy (x, y, height, type)
	int Enemy[8][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
	// ei-Enemy Index, eGap-Enemy Gap, ew-Enemy Width, eStep-Enemy Step
	int ei = 1, eGap = 100, ew = 20, eStep = 10, NoEnemies = 8;
	
	// Player Variables
	// px-Player X, py-Player Y, pSize-Player Size, pStep-Player Step
	int px = (ScWidth-400)/2, py = 300 - 2, pSize = 20;
	
	
	// Line Variables
	int linex = px+pSize, liney = py+pSize;
	
	// Generate First Enemy
	Enemy[0][0] = ScWidth-OpWidth; // set Initial X Pos of Enemy
	Enemy[0][1] = liney+2; // generate random y position of enemy
	Enemy[0][2] = pSize; // set height of enemy
			
	while(1){
		setcolor(WHITE);
		// draw borders
		rectangle(0,0,ScWidth-OpWidth,ScHeight);
		rectangle(ScWidth-OpWidth,0,ScWidth,ScHeight);
		
		// draw Line
		line(0,liney,ScWidth-OpWidth,liney );
		
		// print score
		// itoa function converts number to character array
		settextstyle(4,0,9);
		if( score<10 )
			outtextxy(ScWidth-270, 250, itoa(score,txtScore,10));
		else if( score>=10 )
			outtextxy(ScWidth-320, 250, itoa(score,txtScore,10));
		
		settextstyle(4,0,1);
		outtextxy(ScWidth-375, 500, "Use Spacebar to Jump"); 
		
		//Draw Enemies
		for(int i=0; i<ei; i++){
			 
			//Draw Enemy
			setcolor(YELLOW);
  		    setfillstyle(1, YELLOW);
			if( Enemy[i][3]==0 ){ // if enemy (triangle) to be generated above line
		    	DrawTriangleDown(Enemy[i][0], Enemy[i][1], Enemy[i][0]+ew, Enemy[i][1]+Enemy[i][2]);
			}else{
	  		    DrawTriangleUp(Enemy[i][0], Enemy[i][1], Enemy[i][0]+ew, Enemy[i][1]+Enemy[i][2]);
			} 
			Enemy[i][0] -= eStep; // update enemy position 
		 	
 			// if enemy covers 1/4 distance generate new enemy
			if( Enemy[i][0] <= 900 && Enemy[i][0] > 900-eStep ){
				if( ei < NoEnemies ){// generate enemy if enemies are less than 4
					ei++; // increment enemy index
					break;
				}
			}
			
			// if enemy goes through left border of screen
			if( Enemy[i][0] < 0 ){
				Enemy[i][0] = ScWidth-OpWidth; //reset enemy x postion
				Enemy[i][3] = rand()%2; // generate random enemy type
				// for even enemies generate random enemy & Fruit
				if( Enemy[i][3] == 0 ){
					Enemy[i][1] = liney;
					Enemy[i][2] = pSize;
				}else{ //for odd enemies generate random enemy & Fruit
				    Enemy[i][1] = liney-pSize;
					Enemy[i][2] = pSize;
				}
			} 
		} 
		
		if(kbhit()){ // if any key is pressed
			option = getch(); // catch character in options variable
			if(option == SPACEBAR){ // if spacebar is pressed
				if( py < liney ) // check if player is above line 
					py += pSize; // move player downward
				else
					py -= pSize; // move player upward
			}
		}
		  
		// Draw Player  
		setcolor(WHITE);
		setfillstyle(1,WHITE);
		bar(px,py,px+pSize,py+pSize);
		
		// Player hit Enemy
		for(int i=0; i<NoEnemies; i++){
			if( px+pSize > Enemy[i][0] && px < Enemy[i][0]+ew ){ 
				if( py+pSize/2 >= Enemy[i][1] && py+pSize/2 <= Enemy[i][1]+Enemy[i][2] ){
					GameOver(); 
					break;
				} 
			}
		} 
		
		// if player goes avoid an enemy then increment score
		for(int i=0; i<NoEnemies; i++){
			if( px+pSize/2 >= Enemy[i][0] && px+pSize/2 <= Enemy[i][0] ){ 
				score++;
			}
		}
		
		delay(40);
		cleardevice();
	}
	
	getch();
	closegraph();
}

    
