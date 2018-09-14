#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum{ RUNNING = 1 };

struct Point
{
	int x, y;
};

struct Line
{
	Point start;
	Point end;
};

struct GraphicElement
{
	enum{ SIZE = 256 };
	unsigned int numLines;
	Line* pLines;
	char name[SIZE];
};

typedef struct
{
	unsigned int numGraphicElements;
	GraphicElement* pElements;
}VectorGraphic;

void InitVectorGraphic(VectorGraphic*);
void AddGraphicElement(VectorGraphic*);
void ReportVectorGraphic(VectorGraphic*);
void CleanUpVectorGraphic(VectorGraphic*);

VectorGraphic Image;


int main()
{
	char response;
	InitVectorGraphic(&Image);

	while (RUNNING)
	{
		printf("\nPlease select an option:\n");
		printf("1. Add a Graphic Element\n");
		printf("2. List the Graphic Elements\n");
		printf("q. Quit\n");
		printf("CHOICE: ");
		fflush(stdin);
		scanf("%c", &response);

		switch (response)
		{
		case '1':AddGraphicElement(&Image); break;
		case '2':ReportVectorGraphic(&Image); break;
		case 'q':CleanUpVectorGraphic(&Image); return 0;
		default:printf("Please enter a valid option\n");
		}
		printf("\n");
	}
}

void InitVectorGraphic(VectorGraphic* vg){
	//vg = (VectorGraphic*) malloc (256*sizeof(VectorGraphic));
	vg->numGraphicElements = 0;
	vg->pElements = (GraphicElement*) malloc (50*sizeof(GraphicElement));;
	for (int i = 0; i < 50; i++){
		vg->pElements[i].pLines = (Line*) malloc (50*sizeof(Line));	
		}
	
}

void AddGraphicElement(VectorGraphic* vg){
	int curr = vg->numGraphicElements; /*For better readability*/
	printf("ADDING A Graphic Element");
	
	/*Name of the new Graphical Element*/
	printf("\nPlease enter the name of the new GraphicElement(<256 characters): ");
	scanf("%s", (vg->pElements[curr].name));

	/*Number of lines in the new Graphical Element*/
	printf("\nHow many lines are there in the new GraphicElement? ");
	scanf("%d", &(vg->pElements[curr].numLines));
	
	/*Scanning the values of the points of the individual lines*/
	for (int i = 0; i < (vg->pElements[curr].numLines); i++){
		printf("\nPlease enter the x coord of the start point of the line index %d:", i);
		scanf("%d", &(vg->pElements[curr].pLines[curr].start.x));
		printf("\nPlease enter the y coord of the start point of the line index %d:", i);
		scanf("%d", &(vg->pElements[curr].pLines[curr].start.y));
		printf("\nPlease enter the x coord of the end point of the line index %d:", i);
		scanf("%d", &(vg->pElements[curr].pLines[curr].end.x));
		printf("\nPlease enter the y coord of the end point of the line index %d:", i);
		scanf("%d", &(vg->pElements[curr].pLines[curr].end.y));
	}
	/*Increasing the counter of the Graphical Element tracker*/
	vg->numGraphicElements++;
	printf("\nCOUNTER: %d", vg->numGraphicElements);
	
}

void ReportVectorGraphic(VectorGraphic* vg){
	printf("\nVectorGraphic Report");
	for (int i = 0; i < (vg->numGraphicElements); i++){
		printf("\nReporting Graphic Element #%d", i);
		printf("\nGraphic Element name: %s", vg->pElements[i].name);
		for (int j = 0; j < (vg->pElements[i].numLines); j++){
			printf("\nLine#%d start x: %d", j, (vg->pElements[i].pLines[j].start.x));
			printf("\nLine#%d start y: %d", j, (vg->pElements[i].pLines[j].start.y));
			printf("\nLine#%d end x: %d", j, (vg->pElements[i].pLines[j].start.x));
			printf("\nLine#%d end x: %d", j, (vg->pElements[i].pLines[j].start.y));
		}
	}
}

void CleanUpVectorGraphic(VectorGraphic* vg){
	for (int i = 0; i < (vg->numGraphicElements); i++){
		free(vg->pElements[i].pLines);	
		}
	free(vg->pElements);
}
