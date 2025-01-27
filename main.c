#include<stdio.h>
#include<string.h>

#define totalfloors 4
#define roomsonfloor 4

int checkUser(char name[], char password[]){
    FILE *users = fopen("records.txt", "r");

    if(users == NULL){
        printf("Error Occured");
    }
    else{
        char name_in[20];
        char pass_in[8];
        char unused;

        while(fgets(name_in, sizeof(name_in), users) != NULL ){
        	
        	name_in[strcspn(name_in, "\n")] = '\0';  // replaces \n with \0 to mark the end of name
            fgets(pass_in, sizeof(pass_in)+1, users);
            pass_in[strcspn(pass_in, "\n")] = '\0'; // replaces \n with \0 to mark the end of password
            
            if(strcmp(name, name_in)==0){
                if(strcmp(password, pass_in)==0){
                    printf("Logged in successfully!\n");
                    fclose(users);
                    return 1;
                }else{
                    printf("Incorrect Password\n");
					return 0;
                }
            }
        }
		printf("User not found\n");
		fclose(users);
		return 0;
    }
};

int createUser(char name[], char password[]){
	FILE *users = fopen("records.txt", "a");
	
	if(users == NULL){
		printf("Error Occured\n");
		return 0;
	}else{
		fputs(name, users);
		fputs(password, users);
		return 1;
	}
}

void availableRooms(){
	FILE *rooms = fopen("roombooking.txt", "r");
	if(rooms == NULL){
		printf("Error Occured\n");
	}else{
		char room;
		char type[4][10] = {"Deluxe", "Premium", "Standard", "Shared"};
		int floor_count = 0; 
		int room_count = 0;
		while(fscanf(rooms, "%c", &room) != EOF){
			if(room == '0'){
				printf("%s Room %d\n", type[floor_count], room_count+1);
			}
			room_count++;
			if(room == '\n'){
				room_count = 0;
				floor_count++;
			}
		}
		fclose(rooms);
	}
};

void bookRoom(int floor, int room){
	char rooms_arr[totalfloors][roomsonfloor+1];
	FILE *rooms = fopen("roombooking.txt", "r");
	if(rooms == NULL){
		printf("Error Occured!");
	}else{
		for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                fscanf(rooms, "%c", &rooms_arr[i][j]);
            }
        }
        fclose(rooms);
		rooms_arr[floor][room] = '1';
	}
	FILE *rooms_new = fopen("roombooking.txt", "w");
	if(rooms == NULL){
		printf("Error Occured!");
	}else{
		for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                fprintf(rooms_new, "%c", rooms_arr[i][j]);
            }
        }
        fclose(rooms);
	}
};

int main(){
    char name[20]; 
    char pass[8];
    int choice=0;
    int floor, room;
    
    printf("------------------------------------------------\n");
    printf("		WELCOME TO KHAN HOTEL           \n");
    printf("		Select an Option                \n");
    printf("		1. Login                        \n");
    printf("		2. Create Account               \n");
    printf("		3. Exit                         \n");
    printf("------------------------------------------------\n");
    scanf("%d", &choice);
    
    switch(choice){
    	case 1:
    		do{
        		printf("Enter username: ");
        		scanf("%s", &name);
        		printf("Enter Password: ");
        		scanf("%s", &pass);
    		}while(checkUser(name, pass) == 0);
    		break;
    	case 2:
    		do{
        		printf("Enter username: ");
        		scanf("%s", &name);
        		printf("Enter Password: ");
        		scanf("%s", &pass);
        		strcat(name, "\n");
        		strcat(pass, "\n");
    		}while(createUser(name, pass) == 0);
    		break;
    
		case 3:
    		return 0;
	}
	while(choice!=3){
	
		printf("------------------------------------------------\n");
		printf("		1. Check Available Rooms                        \n");
	    printf("		2. Book A Room               \n");
	    printf("		3. Exit                         \n");
	    printf("------------------------------------------------\n");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				printf("--------------------------------------\n");
				printf("          Available Rooms\n");
				printf("--------------------------------------\n");
				availableRooms();
				break;
			case 2:
				printf("------------------------------------------------\n");
				printf("		1. Delux Room                        \n");
	    		printf("		2. Premium Room               \n");
	    		printf("		3. First Class                         \n");
	    		printf("		4. Shared                         \n");
				printf("------------------------------------------------\n");
				scanf("%d", &floor);
				printf("Enter Room Number from available rooms of this category: ");
				scanf("%d", &room);
				bookRoom(floor-1, room-1);
		}
		printf("Press 3 to exit or any other number to continue");
		scanf("%d", &choice);
	}
	return 0;
    
}
