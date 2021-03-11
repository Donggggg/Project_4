#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

//menu select
static char *choices[] = {
                        "1. SUDOKU",
                        "2. MAZE",
                        (char *)NULL,
                  };

//print ddok ddok logo
static void print_logo(WINDOW *my_menu_win);
void select_game()
{	
        //menu seletions in MENU
        ITEM **my_items;
	int c;			
        //MENU WINDOW
	MENU *my_menu;
        //MAIN WINDOW
        WINDOW *my_menu_win;
        int n_choices, i;
	
        //Init curses
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);

        //create menu seletions
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)malloc(n_choices* sizeof(ITEM *));

        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i],"");

	//create menu window
        my_menu = new_menu((ITEM **)my_items);

        //create main menu window
        my_menu_win = newwin(30, 70, 4, 4);
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        //?? should to googling
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 17, 3, 1));

        //point user selection
        set_menu_mark(my_menu, "--> ");
        
        //print title and ddok ddok
        box(my_menu_win, 0, 0);
	mvwprintw(my_menu_win, 1, 30, "%s", "Game Menu");
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 68);
	mvprintw(LINES - 2, 34, "ddok ddok");
        print_logo(my_menu_win);
        box(my_menu_win, 0, 0);
        refresh();
        
	//post menu in window
	post_menu(my_menu);
	wrefresh(my_menu_win);
        int flag=0,level=1;
        enum{SUDOKU=1,MAZE};
	while((c = wgetch(my_menu_win)) != KEY_F(2))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
                        case KEY_LEFT:
                                if(level>1) level-=1;
                                //mvwprintw(my_menu_win,30,8,"%d",level);
	                        mvprintw(LINES - 2, 34, "LEVEL : %d              ",level);
                                break;
                        case KEY_RIGHT:
                                if(level<10) level+=1;
                                mvprintw(LINES-2,34,"LEVEL : %d"                 ,level);
                                break; 
			case 10: //enter
                                        flag=1;
                                        clear();
                                        startMaze(1,level,NULL);
                                        clear();
                                        break;
                                }
			

                if(flag) break;
                box(my_menu_win, 0, 0);
                refresh(); 
	        post_menu(my_menu);
        	wrefresh(my_menu_win);

	}
		
        //free all
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
}
static void print_logo(WINDOW *my_menu_win)
{
        char line[255];
	FILE *fp;
        fp=fopen("test.txt","r");
        if(fp==NULL)    err(EXIT_FAILURE,"NO test.txt file");
        int i=12;
        while(fgets(line,sizeof(line),fp)!=NULL)
	        mvwprintw(my_menu_win, i++, 4, "%s", line);
}
