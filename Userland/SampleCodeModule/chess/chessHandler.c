#include <chess.h>
#include <standardIO.h>
#include <string.h>
#include <chessHandler.h>
#include <syscalls.h>
#define SCREEN_HEIGTH 16
#define YELLOW_GREETING 0xFFE81F
#define MIDDLE_TITLE 296


/*
Hola, esta es la funcion que llamamos desde apps para poder ejecutar el juego de ajedrez.
Esta en una clase aparte por que es mucho codigo que no aporta a la logica del apps y nada mas molesta en espacio.
*/

void greeting();
char askYesNo();
void printChessMenu();

void chessHandler(int args, char argv[][25]){
    if (args == 0 || strcmp(argv[1],"new")== 0 ||strcmp(argv[1],"-n")==0|| strcmp(argv[1],"start")== 0 ||strcmp(argv[1],"-s")== 0){
        if (hasPrevGame()) println("There's a game already loaded. Are you sure you want to start a new one? [Y/n]");
        else println("You're about to start a new chess game. Are you sure? [Y/n]");
            askYesNo();        
    }else if (strcmp(argv[1],"resume")== 0 ||strcmp(argv[1],"-r")== 0||strcmp(argv[1],"continue")== 0 ||strcmp(argv[1],"-c")== 0){
            if (hasPrevGame()){
                println("Please wait! The game will resume just from where you left it!");
                runChess(1);
            }else{
                println("There doesn't seem to be a previous game saved in memory. Start a new game? [Y/n]");
                askYesNo();
            }     
    }else if (strcmp(argv[1],"help")== 0 ||strcmp(argv[1],"-h")== 0||strcmp(argv[1],"menu")== 0 ||strcmp(argv[1],"-m")== 0){
        printChessMenu();
    }else{
        print(argv[1]);println(": command not found");
    } 
    return;  
}

void printChessMenu(){
    int color = 0xf03fcd;
        printc("chess new, -n", color); printc(": ", color);
        printcln("   Starts a new chess game.", 0xcfd7e6);
        printc("chess resume, -r", color);printc(": ", color);
        printcln("Resumes last loaded game.", 0xcfd7e6);
        printc("chess help, -h", color);printc(": ", color);
        printcln("  Displays a menu with the different valid options.", 0xcfd7e6);
}

char askYesNo(){
    char ans;
    while ((ans != 'n' ) && ans != 'Y'){
            while((ans = getChar())){
                if (ans!=0){
                    if (ans == 'n'){
                        println("Need help? Enter chess help or chess -h to display a menu of the different options from which you can choose");
                        break;
                    }else if(ans == 'Y'){
                        greeting(); //starting a new chess game
                        runChess(0);
                        break;
                    }else{
                        println("Invalid option. Please enter 'Y' if you want to start a new chess game. If not, enter 'n'.");
                        break;
                    }  
                }
            }
        }
    return ans;
}

void greeting(){
    int heigth = 0;
    clearScreen();
    printcFrom("  ______  __    __   _______     _______.     _______.",heigth+=SCREEN_HEIGTH,MIDDLE_TITLE,YELLOW_GREETING);
    printcFrom(" /      ||  |  |  | |   ____|   /       |    /       |",heigth+=SCREEN_HEIGTH,MIDDLE_TITLE,YELLOW_GREETING);
    printcFrom("|  ,----'|  |__|  | |  |__     |   (----`   |   (----`",heigth+=SCREEN_HEIGTH,MIDDLE_TITLE,YELLOW_GREETING);
    printcFrom("|  |     |   __   | |   __|     \\   \\        \\   \\    ",heigth+=SCREEN_HEIGTH,MIDDLE_TITLE,YELLOW_GREETING);
    printcFrom("|  `----.|  |  |  | |  |____.----)   |   .----)   |   ",heigth+=SCREEN_HEIGTH,MIDDLE_TITLE,YELLOW_GREETING);
    printcFrom(" \\______||__|  |__| |_______|_______/    |_______/    ",heigth+=SCREEN_HEIGTH,MIDDLE_TITLE,YELLOW_GREETING);
    heigth+=SCREEN_HEIGTH*2;
    printFrom("In an OS far, far away...",heigth+=SCREEN_HEIGTH,416);
    heigth+=SCREEN_HEIGTH;
    printFrom("Instructions:",heigth+=SCREEN_HEIGTH,0);
    printFrom("Press ENTER to begin your adventure",heigth+=SCREEN_HEIGTH,0);
    printFrom("Press \"q\" to quit without saving or \"p\" to pause your game",heigth+=SCREEN_HEIGTH,0);
    printFrom("Insert your game plays in the following notation:",heigth+=SCREEN_HEIGTH,0);
    printFrom("First, the coordinates of the piece you want to move, then to where you want to move it",heigth+=SCREEN_HEIGTH,0);
    printFrom("For example, a1a3 moves the piece from the position a1 to a3",heigth+=SCREEN_HEIGTH,0);
    heigth+=SCREEN_HEIGTH;
    printFrom("Dont worry if you mistype or enter an invalid move! We will take care of that!",heigth+=SCREEN_HEIGTH,0);
    printFrom("Enjoy!",heigth+=SCREEN_HEIGTH,0);
    while ((getChar())!='\n');
}