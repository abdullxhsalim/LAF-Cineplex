#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "headerFile.h"
#define MAX_MOVIES 5
#define MAX_USERS 100
#define MAX_ADMINS 100

typedef struct str
{
    int serial;
    char name[20];
    int duration;
    int slotNo;
    struct slotData
    {
        char wday[10];
        int hour;
        int min;
        char seats[25][3];
    } slot[2];
} movieData;
typedef struct str2
{
    char username[15];
    char password[30];
} adminData;
typedef struct str3
{
    char username[15];
    char password[20];
    int movieFlag;
    int movieCount;
    movieData movie[MAX_MOVIES];
} userData;
void keyPress()
{
    printf("Press ENTER to continue...");
    getchar();
}
void welcome()
{
    printf(".____       _____  ___________ _________ .__                     .__                 \n");
    printf("|    |     /  _  \\ \\_   _____/ \\_   ___ \\|__| ____   ____ ______ |  |   ___  ___  ___\n");
    printf("|    |    /  /_\\  \\ |    __)   /    \\  \\/|  |/    \\_/ __ \\____ \\ |  | _/ __\\ \\  \\/  /\n");
    printf("|    |___/    |    \\|     \\    \\     \\___|  |   |  \\  ___/|  |_> >  |_\\  ___/ >    < \n");
    printf("|_______ \\____|__  /\\___  /     \\______  /__|___|  /\\___  >   __/|____/\\___  >__/\\_ \\\n");
    printf("        \\/       \\/     \\/             \\/        \\/     \\/|__|             \\/      \\/\n");
    printf("\n\n");
}
void adminRegister()
{
    adminData sampleAdmin;
    FILE *adminFile = fopen("adminFile.bin", "ab");
    printf("Enter username (Max 15 characters, leading spaces will be ignored):\n> ");
    scanf(" %[^\n]", sampleAdmin.username);
    printf("Enter password (Max 30 characters, leading spaces will be ignored):\n> ");
    scanf(" %[^\n]", sampleAdmin.password);
    fwrite(&sampleAdmin, sizeof(adminData), 1, adminFile);
    fclose(adminFile);
}
int adminLogin()
{
    adminData sampleAdmin;
    adminData readAdmin;
    int flag = 0;
    FILE *adminFile = fopen("adminFile.bin", "rb");
    printf("Enter username:\n> ");
    scanf(" %[^\n]", sampleAdmin.username);
    printf("Enter password:\n> ");
    scanf(" %[^\n]", sampleAdmin.password);
    while (fread(&readAdmin, sizeof(adminData), 1, adminFile))
    {
        if (strcmp(sampleAdmin.username, readAdmin.username) == 0 && strcmp(sampleAdmin.password, readAdmin.password) == 0)
        {
            flag = 1;
            break;
        }
    }
    fclose(adminFile);
    if (flag == 1)
    {
        printf("Welcome %s, you are now successfully logged in.", sampleAdmin.username);
        return 1;
    }
    else
    {
        printf("Username or password is incorrect.");
        return 0;
    }
}
void addMovies()
{
    movieData sampleMovie;
    int n;
    FILE *movieFile;
    int movieCount;
    char day[10], seat[3];
    if (fopen("movieFile.bin", "rb") == NULL)
    {
        movieCount = 0;
        movieFile = fopen("movieFile.bin", "ab");
    }
    else
    {
        movieFile = fopen("movieFile.bin", "ab");
        FILE *movieSerialCounter = fopen("movieFile.bin", "rb");
        fseek(movieSerialCounter, -sizeof(movieData), SEEK_END);
        fread(&sampleMovie, sizeof(movieData), 1, movieSerialCounter);
        fclose(movieSerialCounter);
        movieCount = sampleMovie.serial;
    }

movieAddCountPromt:
    printf("How many movies to add? (Max %d)\n> ", MAX_MOVIES - movieCount);
    scanf("%d", &n);
    if (n > MAX_MOVIES - movieCount)
    {
        printf("Sorry! Only %d movies can be added. \n", MAX_MOVIES - movieCount);
        goto movieAddCountPromt;
    }

    for (int i = 0; i < n; ++i)
    {
        sampleMovie.serial = i + 1 + movieCount;
        system("cls");
        printf("Enter the name of the movie no. %d:\n> ", sampleMovie.serial);
        scanf(" %[^\n]", sampleMovie.name);
        printf("Enter movie duration: ");
        scanf("%d", &sampleMovie.duration);
        for (int j = 0; j < 2; ++j)
        {
        dayPrompt:
            printf("\n");
            printf("Enter the day of the week for the slot no. %d\n> ", j + 1);
            scanf(" %[^\n]", sampleMovie.slot[j].wday);
            scanf("");
            if (strcmp(sampleMovie.slot[j].wday, "Sunday") == 0)
                ;
            else if (strcmp(sampleMovie.slot[j].wday, "Monday") == 0)
                ;
            else if (strcmp(sampleMovie.slot[j].wday, "Tuesday") == 0)
                ;
            else if (strcmp(sampleMovie.slot[j].wday, "Wednesday") == 0)
                ;
            else if (strcmp(sampleMovie.slot[j].wday, "Thursday") == 0)
                ;
            else if (strcmp(sampleMovie.slot[j].wday, "Friday") == 0)
                ;
            else if (strcmp(sampleMovie.slot[j].wday, "Saturday") == 0)
                ;
            else
            {
                printf("ERROR! Invalid input.\n");
                goto dayPrompt;
            }
            printf("Enter the starting time for the %s slot (HH:MM):\n> ", sampleMovie.slot[j].wday);
            scanf("%d:%d", &sampleMovie.slot[j].hour, &sampleMovie.slot[j].min);
            printf("Enter the seats pre-occupied for the slot: (Enter 0 to exit)\n> ");
            int k = 0;
            while (k < 25)
            {
                scanf("%s", sampleMovie.slot[j].seats[k]);
                if (strcmp(sampleMovie.slot[j].seats[k++], "0") == 0)
                    break;
            }
        }
        fwrite(&sampleMovie, sizeof(movieData), 1, movieFile);
    }
    printf("Movies added successfully!\n");
    fclose(movieFile);
}
void viewMovies()
{
    movieData sampleMovie;
    FILE *movieFile = fopen("movieFile.bin", "rb");
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        printf("Serial no: %d\t\tName: %s\t\tDuration: %d minutes\n", sampleMovie.serial, sampleMovie.name, sampleMovie.duration);
        for (int i = 0; i < 2; ++i)
        {
            printf("Slot %d:\n\t%s at %02d:%02d\n\tOccuiped seats: ", i + 1, sampleMovie.slot[i].wday, sampleMovie.slot[i].hour, sampleMovie.slot[i].min);
            int j = 0;
            while (strcmp(sampleMovie.slot[i].seats[j], "0") != 0)
                printf("%s ", sampleMovie.slot[i].seats[j++]);
            printf("\n");
        }
        printf("\n");
    }
    fclose(movieFile);
}
void searchMovies()
{
    movieData sampleMovie;
    char key[30];
    FILE *movieFile = fopen("movieFile.bin", "rb");
    printf("What to search for?\n> ");
    scanf(" %[^\n]", key);
    printf("\nSearch results:\n\n");
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (strstr(sampleMovie.name, key) != NULL)
        {
            printf("Serial no: %d\t\tName: %s\t\tDuration: %d minutes\n", sampleMovie.serial, sampleMovie.name, sampleMovie.duration);
            for (int i = 0; i < 2; ++i)
            {
                printf("Slot %d:\n\t%s at %02d:%02d\n\tOccuiped seats: ", i + 1, sampleMovie.slot[i].wday, sampleMovie.slot[i].hour, sampleMovie.slot[i].min);
                int j = 0;
                while (strcmp(sampleMovie.slot[i].seats[j], "0") != 0)
                    printf("%s ", sampleMovie.slot[i].seats[j++]);
                printf("\n");
            }
            printf("\n");
        }
    }
    fclose(movieFile);
}
void deleteMovies()
{
    system("cls");
    viewMovies();
    movieData sampleMovie;
    int serial;
    char serialStr[3];
    FILE *movieFile = fopen("movieFile.bin", "rb");
    FILE *tempFile = fopen("tempFile.bin", "wb");
    int flag = 0;
    printf("Enter the serial number of the movie to be deleted: ");
    scanf("%d", &serial);
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (serial == sampleMovie.serial)
        {
            flag = 1;
        }
        else if (sampleMovie.serial != serial && flag == 1)
        {
            sampleMovie.serial -= 1;
            fwrite(&sampleMovie, sizeof(movieData), 1, tempFile);
        }
        else if (sampleMovie.serial != serial && flag == 0)
            fwrite(&sampleMovie, sizeof(movieData), 1, tempFile);
    }
    fclose(movieFile);
    fclose(tempFile);
    remove("movieFile.bin");
    rename("tempFile.bin", "movieFile.bin");
    if (fopen("movieFile.bin", "rb") == NULL)
    {
        remove("movieFile.bin");
        return;
    }

    userData sampleUser;
    FILE *userFile = fopen("userFile.bin", "rb");
    FILE *tempUserFile = fopen("tempUserFile.bin", "wb");
    int k, serialNo;
    while (fread(&sampleUser, sizeof(userData), 1, userFile))
    {
        int flag = 0;
        for (k = 0; k < sampleUser.movieCount; ++k)
        {
            if (serial == sampleUser.movie[k].serial)
            {
                flag = 1;
                serialNo = k;
                break;
            }
        }
        if (flag == 0)
            fwrite(&sampleUser, sizeof(userData), 1, tempUserFile);
        else if (flag == 1)
        {
            for (int j = serialNo; j < sampleUser.movieCount; ++j)
            {
                sampleUser.movie[j].serial = sampleUser.movie[j + 1].serial;
                strcpy(sampleUser.movie[j].name, sampleUser.movie[j + 1].name);
                sampleUser.movie[j].duration = sampleUser.movie[j + 1].duration;
                for (int k = 0; k < 2; ++k)
                {
                    strcpy(sampleUser.movie[j].slot[k].wday, sampleUser.movie[j + 1].slot[k].wday);
                    sampleUser.movie[j].slot[k].hour = sampleUser.movie[j + 1].slot[k].hour;
                    sampleUser.movie[j].slot[k].min = sampleUser.movie[j + 1].slot[k].min;
                    int l = 0;
                    while (strcmp(sampleUser.movie[j].slot[k].seats[l], "0") != 0)
                    {
                        strcpy(sampleUser.movie[j].slot[k].seats[l], sampleUser.movie[j + 1].slot[k].seats[l]);
                        l++;
                    }
                    strcpy(sampleUser.movie[j].slot[k].seats[l], "0");
                }
            }
            sampleUser.movieCount -= 1;
            if (sampleUser.movieCount == 1)
                sampleUser.movieFlag = 0;
            fwrite(&sampleUser, sizeof(userData), 1, tempUserFile);
        }
    }
    fclose(userFile);
    fclose(tempUserFile);
    remove("userFile.bin");
    rename("tempUserFile.bin", "userFile.bin");
    system("cls");
    printf("Movie deleted successfully!\n");
}
void editSlots()
{
    printf("The following slots are currently in the database: \n");
    viewMovies();
    movieData sampleMovie;
    int serial;
editPrompt:
    printf("Enter the serial no. of the movie whose slot is to be edited:\n> ");
    scanf("%d", &serial);
    int serialMatchFlag = 0;
    FILE *movieFile = fopen("movieFile.bin", "rb");
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (serial == sampleMovie.serial)
        {
            serialMatchFlag = 1;
            break;
        }
    }
    if (serialMatchFlag == 0)
    {
        printf("Serial no. does not exist.\n");
        keyPress();
        getchar();
        system("cls");
        goto editPrompt;
    }
    fclose(movieFile);
    movieFile = fopen("movieFile.bin", "rb");
    FILE *tempFile = fopen("tempFile.bin", "wb");
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (serial != sampleMovie.serial)
            fwrite(&sampleMovie, sizeof(movieData), 1, tempFile);
        else
        {
            for (int j = 0; j < 2; ++j)
            {
            dayPrompt:
                system("cls");
                printf("Enter the day of the week for the slot no. %d:\n> ", j + 1);
                scanf(" %[^\n]", sampleMovie.slot[j].wday);
                scanf("");
                if (strcmp(sampleMovie.slot[j].wday, "Sunday") == 0)
                    ;
                else if (strcmp(sampleMovie.slot[j].wday, "Monday") == 0)
                    ;
                else if (strcmp(sampleMovie.slot[j].wday, "Tuesday") == 0)
                    ;
                else if (strcmp(sampleMovie.slot[j].wday, "Wednesday") == 0)
                    ;
                else if (strcmp(sampleMovie.slot[j].wday, "Thursday") == 0)
                    ;
                else if (strcmp(sampleMovie.slot[j].wday, "Friday") == 0)
                    ;
                else if (strcmp(sampleMovie.slot[j].wday, "Saturday") == 0)
                    ;
                else
                {
                    printf("ERROR! Please enter the name of any day of the week\n");
                    goto dayPrompt;
                }
                printf("Enter the starting time for the %s slot (HH:MM):\n> ", sampleMovie.slot[j].wday);
                scanf("%d:%d", &sampleMovie.slot[j].hour, &sampleMovie.slot[j].min);
                printf("Enter the seats pre-occupied for the slot: (Enter 0 to exit)\n");
                int k = 0;
                while (k < 25)
                {
                    scanf(" %[^\n]", sampleMovie.slot[j].seats[k++]);
                    if (strcmp(sampleMovie.slot[j].seats[k - 1], "0") == 0)
                        break;
                }
            }
            fwrite(&sampleMovie, sizeof(movieData), 1, tempFile);
        }
    }
    fclose(movieFile);
    fclose(tempFile);
    remove("movieFile.bin");
    rename("tempFile.bin", "movieFile.bin");
    system("cls");
    printf("Slot edited successfully!\n");
}
void userRegister()
{
    userData sampleUser;
    FILE *userFile = fopen("userFile.bin", "ab");
    printf("Enter username (Max 15 characters, leading spaces will be ignored):\n> ");
    scanf(" %[^\n]", sampleUser.username);
    printf("Enter password (Max 30 characters, leading spaces will be ignored):\n> ");
    scanf(" %[^\n]", sampleUser.password);
    sampleUser.movieFlag = 0;
    sampleUser.movieCount = 0;
    fwrite(&sampleUser, sizeof(userData), 1, userFile);
    fclose(userFile);
}
int userLogin(char pusername[], char ppassword[])
{
    system("cls");
    userData sampleUser;
    userData readUser;
    int flag = 0;
    FILE *userFile = fopen("userFile.bin", "rb");
    printf("Enter username:\n> ");
    scanf(" %[^\n]", sampleUser.username);
    printf("Enter password:\n> ");
    scanf(" %[^\n]", sampleUser.password);
    while (fread(&readUser, sizeof(userData), 1, userFile))
    {
        if (strcmp(sampleUser.username, readUser.username) == 0 && strcmp(sampleUser.password, readUser.password) == 0)
        {
            flag = 1;
            break;
        }
    }
    fclose(userFile);
    if (flag == 1)
    {
        printf("Welcome %s, you are now successfully logged in.", sampleUser.username);
        strcpy(pusername, sampleUser.username);
        strcpy(ppassword, sampleUser.password);
        return 1;
    }
    else if (flag == 0)
    {
        printf("Username or password is incorrect. ");
        return 0;
    }
}
void bookSeat(char pusername[], char ppassword[])
{
    int serial;
    int slot;
    int seatCounter = 0;
    int slotForSeat;
    char seat[3];
    movieData sampleMovie;
    movieData storedMovie;
    FILE *movieFile = fopen("movieFile.bin", "rb");
serialMatch:
    system("cls");
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        printf("Serial no: %d\t\tName: %s\t\tDuration: %d minutes\n", sampleMovie.serial, sampleMovie.name, sampleMovie.duration);
        for (int i = 0; i < 2; ++i)
        {
            printf("Slot %d:\t%s at %02d:%02d\t\n", i + 1, sampleMovie.slot[i].wday, sampleMovie.slot[i].hour, sampleMovie.slot[i].min);
        }
        printf("\n");
    }
    fclose(movieFile);
    printf("\n");
    movieFile = fopen("movieFile.bin", "rb");
    printf("Enter the serial no. of the movie you want to book: (0 to go back)\n> ");
    scanf("%d", &serial);
    if (serial == 0)
    {
        fclose(movieFile);
        return;
    }
    int serialMatchFlag = 0;
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (serial == sampleMovie.serial)
        {
            serialMatchFlag = 1;
            rewind(movieFile);
            break;
        }
    }
    if (serialMatchFlag == 0)
    {
        printf("Serial no. does not exist.\n");
        keyPress();
        getchar();
        rewind(movieFile);
        goto serialMatch;
    }
    FILE *tempMovieFile = fopen("tempMovieFile.bin", "wb");
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (serial != sampleMovie.serial)
        {
            fwrite(&sampleMovie, sizeof(movieData), 1, tempMovieFile);
        }
        else
        {
            system("cls");
            printf("Serial no: %d\t\tName: %s\t\tDuration: %d minutes\n", sampleMovie.serial, sampleMovie.name, sampleMovie.duration);
            for (int i = 0; i < 2; ++i)
            {
                printf("Slot %d:\t%s at %02d:%02d\t\n", i + 1, sampleMovie.slot[i].wday, sampleMovie.slot[i].hour, sampleMovie.slot[i].min);
            }
            printf("\n");
        slotPrompt:
            printf("Enter the slot no. you want to book:\n> ");
            scanf("%d", &slot);
            slotForSeat = slot;
            char seatNumbers[25][3] = {"A1", "A2", "A3", "A4", "A5",
                                       "B1", "B2", "B3", "B4", "B5",
                                       "C1", "C2", "C3", "C4", "C5",
                                       "D1", "D2", "D3", "D4", "D5",
                                       "E1", "E2", "E3", "E4", "E5"};
        seatPrompt:
            if (slot == 1)
            {
                int seatCounter = 0;
                while (strcmp(sampleMovie.slot[0].seats[seatCounter], "0") != 0)
                    seatCounter++;
                printf("The following seats are available:\n");
                for (int i = 0; i < 25; ++i)
                {
                    int seatDupFlag = 0;
                    for (int j = 0; j < seatCounter; ++j)
                    {
                        if (strcmp(seatNumbers[i], sampleMovie.slot[0].seats[j]) == 0)
                        {
                            seatDupFlag = 1;
                            break;
                        }
                    }
                    if (seatDupFlag == 1)
                    {
                        printf("   ", seatNumbers[i]);
                    }
                    else
                    {
                        printf("%s ", seatNumbers[i]);
                    }
                    if (i == 4 || i == 9 || i == 14 || i == 19)
                        printf("\n");
                }
                printf("\n");
                printf("Enter the seat no. you want to book:\n> ");
                scanf(" %[^\n]", seat);
                int seatAcceptanceFlag1 = 0;
                int seatAcceptanceFlag2 = 1;
                for (int i = 0; i < 25; ++i)
                {
                    if (strcmp(seat, seatNumbers[i]) == 0)
                    {
                        seatAcceptanceFlag1 = 1;
                        break;
                    }
                }
                for (int i = 0; i < seatCounter; ++i)
                {
                    if (strcmp(seat, sampleMovie.slot[0].seats[i]) == 0)
                    {
                        seatAcceptanceFlag2 = 0;
                        break;
                    }
                }
                if (!(seatAcceptanceFlag1 == 1 && seatAcceptanceFlag2 == 1))
                {
                    printf("Invalid seat no.\n");
                    keyPress();
                    getchar();
                    system("cls");
                    goto seatPrompt;
                }
                strcpy(sampleMovie.slot[0].seats[seatCounter++], seat);
                strcpy(sampleMovie.slot[0].seats[seatCounter], "0");
                printf("Seat booked successfully!\n");
                keyPress();
            }
            else if (slot == 2)
            {
                int seatCounter = 0;
                while (strcmp(sampleMovie.slot[1].seats[seatCounter], "0") != 0)
                    seatCounter++;
                printf("The following seats are available:\n");
                for (int i = 0; i < 25; ++i)
                {
                    int seatDupFlag = 0;
                    for (int j = 0; j < seatCounter; ++j)
                    {
                        if (strcmp(seatNumbers[i], sampleMovie.slot[1].seats[j]) == 0)
                        {
                            seatDupFlag = 1;
                            break;
                        }
                    }
                    if (seatDupFlag == 1)
                    {
                        printf("   ", seatNumbers[i]);
                    }
                    else
                    {
                        printf("%s ", seatNumbers[i]);
                    }
                    if (i == 4 || i == 9 || i == 14 || i == 19)
                        printf("\n");
                }
                printf("\n");
                printf("Enter the seat no. you want to book:\n> ");
                scanf(" %[^\n]", seat);
                int seatAcceptanceFlag1 = 0;
                int seatAcceptanceFlag2 = 1;
                for (int i = 0; i < 25; ++i)
                {
                    if (strcmp(seat, seatNumbers[i]) == 0)
                    {
                        seatAcceptanceFlag1 = 1;
                        break;
                    }
                }
                for (int i = 0; i < seatCounter; ++i)
                {
                    if (strcmp(seat, sampleMovie.slot[1].seats[i]) == 0)
                    {
                        seatAcceptanceFlag2 = 0;
                        break;
                    }
                }
                if (!(seatAcceptanceFlag1 == 1 && seatAcceptanceFlag2 == 1))
                {
                    printf("Invalid seat no.\n");
                    keyPress();
                    getchar();
                    system("cls");
                    goto seatPrompt;
                }
                strcpy(sampleMovie.slot[1].seats[seatCounter++], seat);
                strcpy(sampleMovie.slot[1].seats[seatCounter], "0");
                printf("Seat booked successfully!\n");
                keyPress();
            }
            else
            {
                printf("Invalid slot no.\n");
                keyPress();
                goto slotPrompt;
            }
            storedMovie = sampleMovie;
            fwrite(&sampleMovie, sizeof(movieData), 1, tempMovieFile);
        }
    }
    fclose(movieFile);
    fclose(tempMovieFile);
    remove("movieFile.bin");
    rename("tempMovieFile.bin", "movieFile.bin");

    FILE *userFile = fopen("userFile.bin", "rb");
    rewind(userFile);
    FILE *tempUserFile = fopen("tempUserFile.bin", "wb");
    rewind(tempUserFile);
    userData sampleUser;
    while (fread(&sampleUser, sizeof(userData), 1, userFile))
    {
        if (strcmp(pusername, sampleUser.username) != 0)
        {
            fwrite(&sampleUser, sizeof(userData), 1, tempUserFile);
        }
        else
        {
            sampleUser.movieFlag = 1;
            sampleUser.movieCount += 1;
            sampleUser.movie[sampleUser.movieCount - 1].slotNo = slotForSeat;
            sampleUser.movie[sampleUser.movieCount - 1].serial = storedMovie.serial;
            strcpy(sampleUser.movie[sampleUser.movieCount - 1].name, storedMovie.name);
            sampleUser.movie[sampleUser.movieCount - 1].duration = storedMovie.duration;
            if (slotForSeat == 1)
            {
                strcpy(sampleUser.movie[sampleUser.movieCount - 1].slot[0].wday, storedMovie.slot[0].wday);
                sampleUser.movie[sampleUser.movieCount - 1].slot[0].hour = storedMovie.slot[0].hour;
                sampleUser.movie[sampleUser.movieCount - 1].slot[0].min = storedMovie.slot[0].min;
                strcpy(sampleUser.movie[sampleUser.movieCount - 1].slot[0].seats[0], seat);
            }
            else if (slotForSeat == 2)
            {
                strcpy(sampleUser.movie[sampleUser.movieCount - 1].slot[1].wday, storedMovie.slot[1].wday);
                sampleUser.movie[sampleUser.movieCount - 1].slot[1].hour = storedMovie.slot[1].hour;
                sampleUser.movie[sampleUser.movieCount - 1].slot[1].min = storedMovie.slot[1].min;
                strcpy(sampleUser.movie[sampleUser.movieCount - 1].slot[1].seats[0], seat);
            }
            fwrite(&sampleUser, sizeof(userData), 1, tempUserFile);
        }
    }
    fclose(userFile);
    fclose(tempUserFile);
    remove("userFile.bin");
    rename("tempUserFile.bin", "userFile.bin");
    system("cls");
    printf("Seat booked successfully!\n");
}
void userBookings(char pusername[], char ppassword[])
{
    FILE *userFile = fopen("userFile.bin", "rb");
    userData sampleUser;
    printf("%s, your bookings are:\n\n", pusername);
    while (fread(&sampleUser, sizeof(userData), 1, userFile))
    {
        if (strcmp(pusername, sampleUser.username) == 0)
        {
            printf("Username: %s\t\tPassword: %s\n", sampleUser.username, sampleUser.password);
            if (sampleUser.movieCount == 0)
            {
                printf("No movies booked\n\n");
            }
            else
            {
                for (int i = 0; i < sampleUser.movieCount; ++i)
                {
                    int j = sampleUser.movie[i].slotNo - 1;
                    printf("Serial no: %d\t\tName: %s\t\tDuration: %d minutes\n", sampleUser.movie[i].serial, sampleUser.movie[i].name, sampleUser.movie[i].duration);
                    printf("Slot %d:\n\t%s at %02d:%02d\nYour seats: ", j + 1, sampleUser.movie[i].slot[j].wday, sampleUser.movie[i].slot[j].hour, sampleUser.movie[i].slot[j].min);
                    printf("%s", sampleUser.movie[i].slot[j].seats[0]);
                    printf("\n\n");
                }
                printf("\n");
            }
        }
    }
    fclose(userFile);
}
void deleteBooking(char pusername[], char ppassword[])
{
    userData sampleUser;
    FILE *userFile = fopen("userFile.bin", "rb");
    while (fread(&sampleUser, sizeof(userData), 1, userFile))
    {
        if (strcmp(pusername, sampleUser.username) == 0)
            break;
    }
    fclose(userFile);

    if (sampleUser.movieCount == 0)
    {
        printf("You have not booked any movies.\n");
        keyPress();
        return;
    }
serialNoPrompt:
    userBookings(pusername, ppassword);
    printf("Enter the serial no. of the movie you want to delete:\n> ");
    int serial;
    scanf("%d", &serial);

    int i;
    int serialMatchFlag = 0;
    for (i = 0; i < sampleUser.movieCount; ++i)
    {
        if (sampleUser.movie[i].serial == serial)
        {
            serialMatchFlag = 1;
            break;
        }
    }
    if (serialMatchFlag == 0)
    {
        system("cls");
        printf("Invalid input. \n");
        keyPress();
        goto serialNoPrompt;
    }
    movieData sampleMovie;
    movieData storedMovie;
    FILE *movieFile = fopen("movieFile.bin", "rb");
    FILE *tempMovieFile = fopen("tempMovieFile.bin", "wb");
    int userMovieNo = i;
    int slot = sampleUser.movie[userMovieNo].slotNo;
    while (fread(&sampleMovie, sizeof(movieData), 1, movieFile))
    {
        if (sampleMovie.serial != serial)
        {
            fwrite(&sampleMovie, sizeof(movieData), 1, tempMovieFile);
        }
        else
        {
            int j = 0;
            while (strcmp(sampleMovie.slot[slot - 1].seats[j], "0") != 0)
            {
                if (strcmp(sampleMovie.slot[slot - 1].seats[j], sampleUser.movie[userMovieNo].slot[slot - 1].seats[0]) == 0)
                {
                    strcpy(sampleMovie.slot[slot - 1].seats[j], sampleMovie.slot[slot - 1].seats[j + 1]);
                    break;
                }
                j++;
            }
            storedMovie = sampleMovie;
            fwrite(&sampleMovie, sizeof(movieData), 1, tempMovieFile);
        }
    }
    printf("\nseat no. %s", sampleUser.movie[userMovieNo].slot[slot - 1].seats[0]);
    fclose(movieFile);
    fclose(tempMovieFile);
    remove("movieFile.bin");
    rename("tempMovieFile.bin", "movieFile.bin");

    userFile = fopen("userFile.bin", "rb");
    FILE *tempUserFile = fopen("tempUserFile.bin", "wb");
    while (fread(&sampleUser, sizeof(userData), 1, userFile))
    {
        if (strcmp(pusername, sampleUser.username) != 0)
        {
            fwrite(&sampleUser, sizeof(userData), 1, tempUserFile);
        }
        else
        {
            for (int i = 0; i < sampleUser.movieCount; ++i)
            {
                if (sampleUser.movie[i].serial == serial)
                {
                    for (int j = i; j < sampleUser.movieCount; ++j)
                    {
                        sampleUser.movie[j].serial = sampleUser.movie[j + 1].serial;
                        strcpy(sampleUser.movie[j].name, sampleUser.movie[j + 1].name);
                        sampleUser.movie[j].duration = sampleUser.movie[j + 1].duration;
                        for (int k = 0; k < 2; ++k)
                        {
                            strcpy(sampleUser.movie[j].slot[k].wday, sampleUser.movie[j + 1].slot[k].wday);
                            sampleUser.movie[j].slot[k].hour = sampleUser.movie[j + 1].slot[k].hour;
                            sampleUser.movie[j].slot[k].min = sampleUser.movie[j + 1].slot[k].min;
                            strcpy(sampleUser.movie[j].slot[k].seats[0], sampleUser.movie[j + 1].slot[k].seats[0]);
                        }
                    }
                }
            }
            sampleUser.movieCount -= 1;
            if (sampleUser.movieCount == 0)
                sampleUser.movieFlag = 0;
            fwrite(&sampleUser, sizeof(userData), 1, tempUserFile);
        }
    }
    fclose(userFile);
    fclose(tempUserFile);
    remove("userFile.bin");
    rename("tempUserFile.bin", "userFile.bin");
    printf(" deleted successfully!\n");
}
void viewUser()
{
    if (fopen("userFile.bin", "rb") == NULL)
    {
        printf("No users found.\n");
        return;
    }
    FILE *userFile = fopen("userFile.bin", "rb");
    userData sampleUser;
    while (fread(&sampleUser, sizeof(userData), 1, userFile))
    {
        printf("Username: %s\t\tPassword: %s\n", sampleUser.username, sampleUser.password);
        if (sampleUser.movieFlag == 0)
        {
            printf("No movies booked\n\n");
            continue;
        }
        for (int i = 0; i < sampleUser.movieCount; ++i)
        {
            printf("Serial no: %d\t\tName: %s\t\tDuration: %d minutes\n", sampleUser.movie[i].serial, sampleUser.movie[i].name, sampleUser.movie[i].duration);
            int j = sampleUser.movie[i].slotNo - 1;
            printf("Slot %d:\n\t%s at %02d:%02d\n\tOccuiped seats: ", j, sampleUser.movie[i].slot[j].wday, sampleUser.movie[i].slot[j].hour, sampleUser.movie[i].slot[j].min);
            printf("%s ", sampleUser.movie[i].slot[j].seats[0]);
            printf("\n");
            printf("\n");
        }
        printf("\n");
    }
}
int main()
{
    system("cls");
    welcome();
    keyPress();
    system("cls");
userOrAdminPrompt1:
    printf("Who is using the program?\n1. User\t\t2. Admin\t\t0. Exit the program\n\n> ");
    int userOrAdminPrompt1;
    scanf("%d", &userOrAdminPrompt1);
    if (userOrAdminPrompt1 == 1) // USER SECTION
    {
    userPrompt1:
        system("cls");
        printf("What would you like to do?\n1. Login\t\t2. Register\t\t3. Go back\t\t0. Exit the program\n\n> ");
        int userPrompt1;
        scanf("%d", &userPrompt1);
        if (userPrompt1 == 1) // USER LOGIN SECTION
        {
            system("cls");
            char pusername[15], ppassword[20];
            if (userLogin(pusername, ppassword) == 1)
            {
                // IF LOGIN IS SUCCESSFUL
                keyPress();
            userPrompt2:
                system("cls");
                printf("What would you like to do?\n1. Book a seat\t\t2. View current bookings\t\t3. Delete a booking\t\t4. Go back\t\t0. Exit the program\n\n> ");
                int userPrompt2;
                scanf("%d", &userPrompt2);
                if (userPrompt2 == 1) // BOOK A SEAT
                {
                    system("cls");
                    bookSeat(pusername, ppassword);
                    keyPress();
                    goto userPrompt2;
                }
                else if (userPrompt2 == 2) // VIEW CURRENT BOOKINGS
                {
                    system("cls");
                    userBookings(pusername, ppassword);
                    keyPress();
                    getchar();
                    goto userPrompt2;
                }
                else if (userPrompt2 == 3) // DELETE A BOOKING
                {
                    system("cls");
                    deleteBooking(pusername, ppassword);
                    keyPress();
                    getchar();
                    goto userPrompt2;
                }
                else if (userPrompt2 == 4) // GO BACK
                {
                    goto userPrompt1;
                }
                else if (userPrompt2 == 0) // EXIT THE PROGRAM
                {
                    return 0;
                }
                else // INVALID INPUT AT USER PROMPT 2
                {
                    printf("Invalid input. Please try again.");
                    keyPress();
                    goto userPrompt2;
                }
            }
            else if (userLogin(pusername, ppassword) == 0)
            {
                // IF LOGIN IS NOT SUCCESSFUL
                keyPress();
                getchar();
                goto userPrompt1;
            }
        }
        else if (userPrompt1 == 2) // USER REGISTER SECTION
        {
            system("cls");
            userRegister();
            keyPress();
            goto userPrompt1;
        }
        else if (userPrompt1 == 3) // GO BACK
        {
            system("cls");
            goto userOrAdminPrompt1;
        }
        else if (userPrompt1 == 0) // EXIT THE PROGRAM
        {
            return 0;
        }
        else // INVALID INPUT AT USER LOGIN PROMPT
        {
            printf("Invalid input. Please try again.\n");
            keyPress();
            goto userPrompt1;
        }
    }
    else if (userOrAdminPrompt1 == 2) // ADMIN SECTION
    {
    adminPrompt1:
        system("cls");
        printf("What would you like to do?\n1. Login\t\t2. Register\t\t3. Go back\t\t0. Exit the program\n\n> ");
        int adminPrompt1;
        scanf("%d", &adminPrompt1);
        system("cls");
        if (adminPrompt1 == 1) // ADMIN LOGIN SECTION
        {
            if (adminLogin() == 1) // IF LOGIN IS SUCCESSFUL
            {
                keyPress();
            adminFunctionalityPrompt1:
                system("cls");
                printf("What would you like to do?\n\n");
                printf("1. Display now showing movies\n");
                printf("2. Search movies\n");
                printf("3. Add movies to the database\n");
                printf("4. Edit slots\n");
                printf("5. Delete movies\n");
                printf("6. View users\n");
                printf("7. Go back\n");
                printf("0. Exit the program\n\n> ");

                int adminFunctionalityPrompt1;
                scanf("%d", &adminFunctionalityPrompt1);
                if (adminFunctionalityPrompt1 == 1)
                {
                    system("cls");
                    viewMovies();
                    keyPress();
                    getchar();
                    goto adminFunctionalityPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 2)
                {
                    system("cls");
                    searchMovies();
                    keyPress();
                    getchar();
                    goto adminFunctionalityPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 3)
                {
                    system("cls");
                    addMovies();
                    keyPress();
                    getchar();
                    goto adminFunctionalityPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 4)
                {
                    system("cls");
                    editSlots();
                    keyPress();
                    getchar();
                    goto adminFunctionalityPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 5)
                {
                    system("cls");
                    deleteMovies();
                    keyPress();
                    getchar();
                    goto adminFunctionalityPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 6)
                {
                    system("cls");
                    viewUser();
                    keyPress();
                    getchar();
                    goto adminFunctionalityPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 7)
                {
                    system("cls");
                    goto adminPrompt1;
                }
                else if (adminFunctionalityPrompt1 == 0)
                {
                    system("cls");
                    return 0;
                }
                else
                {
                    printf("Invalid input. Please try again.\n");
                    keyPress();
                    goto adminFunctionalityPrompt1;
                }
                system("cls");
            }
            else if (adminLogin() == 0)
            {
                // IF LOGIN IS NOT SUCCESSFUL
                keyPress();
                system("cls");
                goto adminPrompt1;
            }
        }
        else if (adminPrompt1 == 2) // ADMIN REGISTER SECTION
        {
            adminRegister();
            keyPress();
            goto adminPrompt1;
        }
        else if (adminPrompt1 == 3) // GO BACK
        {
            goto userOrAdminPrompt1;
        }
        else if (adminPrompt1 == 0) // EXIT THE PROGRAM
        {
            return 0;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
            keyPress();
            goto adminPrompt1;
        }
    }
    else if (userOrAdminPrompt1 == 0) // EXIT THE PROGRAM
    {
        return 0;
    }
    else // INVALID INPUT AT USER OR ADMIN PROMPT
    {
        printf("Invalid input. Please try again.\n");
        keyPress();
        goto userOrAdminPrompt1;
    }
    return 0;
}