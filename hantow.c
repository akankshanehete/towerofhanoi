#include <stdio.h>
#include <string.h>
#include <unistd.h>


/* this function adds a new disk on top of the desired peg */
void addtoPeg(int peg[],int disk_size){
    int i = 0;
    for( i = 0; i < 9;i++){
        if( peg[i] == 0){
            peg[i] = disk_size;
            break;
        }
    }
}

/* this function removes the topmost disk from the desired peg */
void rmfromPeg(int peg[],int disk_size){
    int i = 0;
    for( i = 0; i < 9;i++){
        if( peg[i] == disk_size){
            peg[i] = 0;
            break;
        }
    }
}

void displaysegment(int num){
    if (num == 0){
        printf("          |               ");
    }
    else if (num == 1){
        printf("         +|+              ");
    }
    else if (num == 2){
        printf("        ++|++             ");

    }
    else if (num == 3){
        printf("       +++|+++            ");
    }
    else if (num == 4){
        printf("      ++++|++++           ");
    }
    else if (num == 5){
        printf("     +++++|+++++          ");
    }
    else if (num == 6){
        printf("    ++++++|++++++         ");

    }
    else if (num == 7){
        printf("   +++++++|+++++++        ");

    }
    else if (num == 8){
        printf("  ++++++++|++++++++       ");

    }
    else if (num == 9){
        printf(" +++++++++|+++++++++      ");

    }
}

/* this function displays the pegs every time a move is made */
void display_pegs(int A[], int B[],int C[]){
    int i = 0;
    for(i = 8; i >=0;i--){
        displaysegment(A[i]);
        displaysegment(B[i]);
        displaysegment(C[i]);
        printf("\n");
    }
    printf("XXXXXXXXXXXXXXXXXXXXX     XXXXXXXXXXXXXXXXXXXXX     XXXXXXXXXXXXXXXXXXXXX \n");
    printf(" \n");
    printf(" \n");
    sleep(1);

}

/* this function prints all the pegs at each move in order */
void printAll(char from_rod, char to_rod, char mid_rod, int frompeg[], int topeg[], int midpeg[]){
    if (to_rod == 'A'){
        if(mid_rod == 'B'){
            display_pegs(topeg,midpeg,frompeg);
        }
        else {
            display_pegs(topeg,frompeg,midpeg);
        }
    }
    else if (mid_rod == 'A'){
        if (to_rod == 'B'){
            display_pegs(midpeg,topeg,frompeg);
        }
        else {
            display_pegs(midpeg,frompeg,topeg);
        }
    }
    else if (from_rod == 'A'){
        if (to_rod == 'B'){
            display_pegs(frompeg,topeg,midpeg);
        }
        else {
            display_pegs(frompeg,midpeg,topeg);
        }
    }


}

void towerOfHanoi(int num_of_disks, char from_rod, char to_rod, char mid_rod, int frompeg[], int topeg[], int midpeg[]){

    if (num_of_disks == 1){
        addtoPeg(topeg,num_of_disks);
        rmfromPeg(frompeg,num_of_disks);
        printAll(from_rod, to_rod, mid_rod, frompeg, topeg, midpeg);
        return;
    }

    towerOfHanoi(num_of_disks-1, from_rod, mid_rod, to_rod, frompeg, midpeg, topeg);
    addtoPeg(topeg,num_of_disks);
    rmfromPeg(frompeg,num_of_disks);
    printAll(from_rod, to_rod, mid_rod, frompeg, topeg, midpeg);
    towerOfHanoi(num_of_disks-1, mid_rod, to_rod, from_rod, midpeg, topeg, frompeg);
}

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Incorrect number of command line arguments. Terminating program...\n");
        return 0;
    }

    if (strlen(argv[1]) != 1){
        printf("Incorrect argument. Terminating program...\n");
        return 0;
    }

    if( argv[1][0]-'0' < 1 || argv[1][0]-'0' > 9){
        printf("Incorrect value of argv[1][0]. Terminating program...\n");
        return 0;
    }

    int num_of_disks = argv[1][0]-'0';

    int pegA[] = {0,0,0,0,0,0,0,0,0};
    int pegB[] = {0,0,0,0,0,0,0,0,0};
    int pegC[] = {0,0,0,0,0,0,0,0,0};


    int i = num_of_disks;

    printf("Number of disks = %d\n\n",num_of_disks);

    /* initializing peg 1 with the appropriate disks */
    for(int j = 0; j < 9; j++){
        pegA[j]=i;
        i--;
        if (i == 0){
            break;
        }
    }

    display_pegs(pegA,pegB,pegC);

    towerOfHanoi(num_of_disks, 'A', 'B', 'C', pegA, pegB, pegC);  // A, B and C are names of rods
    printf("done\n");
    return 0;
}
