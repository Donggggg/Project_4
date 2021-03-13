#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

static char *choices[] = {
                        "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
			"Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
			"Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
			"Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
                        "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
			"Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
			"Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
			"Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
                        "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
			"Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
			"Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
			"Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
                        "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
			"Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
			"Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
			"Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
                        "Exit",
                        (char *)NULL,
                  };

void show_rank()
{
        ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *win;
        int n_choices, i;
	
	//init ncurses window
        initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
        init_pair(1, COLOR_RED,COLOR_YELLOW);
	//create rank list
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)malloc(n_choices* sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], choices[i]);

	//create menu window
	my_menu = new_menu((ITEM **)my_items);
	menu_opts_off(my_menu, O_SHOWDESC);//only show 1 list  per line

        
        //create main window
        win = newwin(30, 70, 4, 4);
        keypad(win, TRUE);
        
        //###############should googling derwin(), set_menu_sub()###################
        set_menu_win(my_menu, win);
        set_menu_sub(my_menu, derwin(win, 25, 68, 3, 1));
	set_menu_format(my_menu, 25, 3);
	set_menu_mark(my_menu, "--> ");

        
        //print border line and title
        box(win, 0, 0);
        mvwprintw(win,0,8,"RANK");	
        mvwprintw(win,0,20,"ID");	
        mvwprintw(win,0,32,"SCORE");
	//print explation at the bottom
        attron(COLOR_PAIR(1));
	mvprintw(LINES - 3, 30, "<--- prev     next--->");
	mvprintw(LINES - 2, 34, "(F2 to Exit)");
	attroff(COLOR_PAIR(1));

        //refresh all
	refresh();
	post_menu(my_menu);
	wrefresh(win);

	while((c = wgetch(win)) != KEY_F(2))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_SCR_UPAGE);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_SCR_DPAGE);
				break;
		}
                wrefresh(win);
	}	

        //free all
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
        endwin();
}