/*This program is about (problem domain) movie management system
    project name: (Start Theater Journey)
    ==== Key features:
        * Add Movie (name, description, time, duration)
        * Edit/Modify movie
        * Delete movie
        * Reservation/Cancel Reservation
        * Revenue Report
*/

// Linking section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define section
#define MAX_MOVIES 100
#define MAX_ROW 10
#define MAX_COLUMN 3
#define TICKET_PRICE 20

// Global declaration section
typedef struct {
    char name[50];
    char description[100];
    char start_time[10];
    int duration;
    int num_reserved_seats;
    int reserved_seats[MAX_ROW][MAX_COLUMN];
} movie_t;

typedef struct {
    char name[50];
    char email[50];
    char reserved_seats[500];
} reservation_t;

// function declaration section
void add_movie(movie_t movies[], int* num_movies);
void modify_movie(movie_t movies[], int num_movies);
void delete_movie(movie_t movies[], int* num_movies);
void reserve_seat(movie_t movies[], int num_movies);
void cancel_reservation(movie_t movies[], int num_movies);
void display_movies(movie_t movies[], int num_movies);
void display_reservations(movie_t movies[], int num_movies);
void generate_revenue_report(movie_t movies[], int num_movies);
void load_movies(movie_t movies[], int* num_movies);
void save_movies(movie_t movies[], int num_movies);

// main function section
int main() {
    movie_t movies[MAX_MOVIES];
    int num_movies = 0;

    load_movies(movies, &num_movies);

    int choice;
    do {
        printf("Movie Reservation System\n");
        printf("------------------------\n");
        printf("1. Add new movie\n");
        printf("2. Modify existing movie\n");
        printf("3. Delete movie\n");
        printf("4. Reserve seat\n");
        printf("5. Cancel reservation\n");
        printf("6. Display all movies\n");
        printf("7. Display reservations for a movie\n");
        printf("8. Generate revenue report\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_movie(movies, &num_movies);
                save_movies(movies, num_movies);
                break;
            case 2:
                modify_movie(movies, num_movies);
                save_movies(movies, num_movies);
                break;
            case 3:
                delete_movie(movies, &num_movies);
                save_movies(movies, num_movies);
                break;
            case 4:
                reserve_seat(movies, num_movies);
                save_movies(movies, num_movies);
                break;
            case 5:
                cancel_reservation(movies, num_movies);
                save_movies(movies, num_movies);
                break;
            case 6:
                display_movies(movies, num_movies);
                break;
            case 7:
                display_reservations(movies, num_movies);
                break;
            case 8:
                generate_revenue_report(movies, num_movies);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        getch();
        system("CLS");
    } while (choice != 9);

    return 0;
}

void load_movies(movie_t movies[], int* num_movies) {
    FILE* fp = fopen("movies.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", num_movies);
        for (int i = 0; i < *num_movies; i++) {
            fscanf(fp, "%s %[^\n] %s %d %d", movies[i].name, movies[i].description, movies[i].start_time, &movies[i].duration, &movies[i].num_reserved_seats);
            for(int j=0; j<MAX_ROW; j++)
                for(int k=0; k<MAX_COLUMN; k++)
                    fscanf(fp, "%d", &movies[i].reserved_seats[j][k]);
        }
        fclose(fp);
    }
}

void save_movies(movie_t movies[], int num_movies) {
    FILE* fp = fopen("movies.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%d\n", num_movies);
        for (int i = 0; i < num_movies; i++) {
            fprintf(fp, "%s\n%s\n%s\n%d\n%d\n", movies[i].name, movies[i].description, movies[i].start_time, movies[i].duration, movies[i].num_reserved_seats);
            for(int j=0; j<MAX_ROW; j++) {
                for(int k=0; k<MAX_COLUMN; k++) {
                    fprintf(fp, "%d ", movies[i].reserved_seats[j][k]);
                }
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
}

void add_movie(movie_t movies[], int* num_movies) {
    if (*num_movies >= MAX_MOVIES) {
        printf("Maximum number of movies reached.\n");
        return;
    }

    movie_t new_movie;
    printf("Enter movie details:\n");
    printf("Name: ");
    fflush(stdin);
    gets(new_movie.name);
    printf("Description: ");
    fflush(stdin);
    gets(new_movie.description);
    printf("Start Time: ");
    fflush(stdin);
    gets(new_movie.start_time);
    printf("Duration (in minutes): ");
    scanf("%d", &new_movie.duration);
    new_movie.num_reserved_seats = 0;

    for(int i=0; i<MAX_ROW; i++)
        for(int j=0; j<MAX_COLUMN; j++)
            new_movie.reserved_seats[i][j] = 0;

    movies[*num_movies] = new_movie;
    (*num_movies)++;

    printf("Movie added successfully.\n");
}

void modify_movie(movie_t movies[], int num_movies) {
    if (num_movies == 0) {
        printf("No movies available to modify.\n");
        return;
    }

    char movie_name[50];
    printf("Enter the name of the movie to modify: ");
    fflush(stdin);
    gets(movie_name);

    int found = 0;
    for (int i = 0; i < num_movies; i++) {
        if (strcmpi(movie_name, movies[i].name) == 0) {
            printf("Enter the updated details for the movie:\n");
            printf("Description: ");
            fflush(stdin);
            gets(movies[i].description);
            printf("Start Time: ");
            fflush(stdin);
            gets(movies[i].start_time);
            printf("Duration (in minutes): ");
            scanf("%d", &movies[i].duration);

            found = 1;
            printf("Movie details modified successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Movie not found.\n");
    }
}

void delete_movie(movie_t movies[], int* num_movies) {
    if (*num_movies == 0) {
        printf("No movies available to delete.\n");
        return;
    }

    char movie_name[50];
    printf("Enter the name of the movie to delete: ");
    fflush(stdin);
    gets(movie_name);

    int found = 0;
    for (int i = 0; i < *num_movies; i++) {
        if (strcmp(movie_name, movies[i].name) == 0) {
            // Shift movies after the deleted movie to the left
            for (int j = i; j < *num_movies - 1; j++) {
                movies[j] = movies[j + 1];
            }

            (*num_movies)--;
            found = 1;
            printf("Movie deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Movie not found.\n");
    }
}

void reserve_seat(movie_t movies[], int num_movies) {
    if (num_movies == 0) {
        printf("No movies available to reserve seats.\n");
        return;
    }

    char movie_name[50];
    printf("Enter the name of the movie to reserve seats: ");
    fflush(stdin);
    gets(movie_name);

    int found = 0;
    for (int i = 0; i < num_movies; i++) {
        if (strcmpi(movie_name, movies[i].name) == 0) {
            if (movies[i].num_reserved_seats >= MAX_ROW*MAX_COLUMN) {
                printf("No seats available for reservation.\n");
                return;
            }

            if (movies[i].num_reserved_seats == 0) {
                printf("No seat reserved yet!\n");
            } else {
                printf("Available seats for %s:\n", movies[i].name);
                printf("-----------------------\n");
                for (int j = 0; j < MAX_ROW; j++) {
                    for(int k = 0; k < MAX_COLUMN; k++) {
                        printf("%d ", movies[i].reserved_seats[j][k]);
                    }

                    printf("\n");
                }
            }
            printf("\n");

            int row, column, reserve_value;
            printf("Enter the seat row-%d & column-%d reserve value (1 2 6): ", MAX_ROW, MAX_COLUMN);
            scanf("%d %d %d", &row, &column, &reserve_value);

            if(row <= MAX_ROW && row > 0 && column <= MAX_COLUMN && column > 0 && movies[i].reserved_seats[row-1][column-1] == 0) {
                movies[i].reserved_seats[row-1][column-1] = reserve_value;
                movies[i].num_reserved_seats++;

                printf("Seat reserved successfully.\n");
                found = 1;
                break;
            }

            if (!found) {
                printf("Invalid seat or seat is already reserved.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("Movie not found.\n");
    }
}

void cancel_reservation(movie_t movies[], int num_movies) {
    if (num_movies == 0) {
        printf("No movies available to cancel reservations.\n");
        return;
    }

    char movie_name[50];
    printf("Enter the name of the movie to cancel reservations: ");
    fflush(stdin);
    gets(movie_name);

    int found = 0;
    for (int i = 0; i < num_movies; i++) {
        if (strcmpi(movie_name, movies[i].name) == 0) {
            if (movies[i].num_reserved_seats == 0) {
                printf("No reservations available for cancellation.\n");
                return;
            }

            printf("Reserved seats for: ");
            puts(movies[i].name);
            printf("\n----------------------\n");
            for (int j = 0; j < MAX_ROW; j++) {
                for(int k = 0; k < MAX_COLUMN; k++) {
                    printf("%d ", movies[i].reserved_seats[j][k]);
                }

                printf("\n");
            }

            printf("\n");

            int row, column, reserve_value;
            printf("Enter the seat row-%d & column-%d cancel value (1 2 6): ", MAX_ROW, MAX_COLUMN);
            scanf("%d %d %d", &row, &column, &reserve_value);

            if(row <= MAX_ROW && row > 0 && column <= MAX_COLUMN && column > 0 && movies[i].reserved_seats[row-1][column-1] == reserve_value) {
                movies[i].reserved_seats[row-1][column-1] = 0;
                movies[i].num_reserved_seats--;

                printf("Reservation canceled successfully.\n");
                found = 1;
                break;
            }

            if (!found) {
                printf("Invalid seat or seat is not reserved.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("Movie not found.\n");
    }
}

void display_movies(movie_t movies[], int num_movies) {
    if (num_movies == 0) {
        printf("No movies available.\n");
        return;
    }

    printf("List of Movies:\n");
    printf("----------------\n");

    for (int i = 0; i < num_movies; i++) {
        printf("Movie %d:\n", i + 1);
        printf("Name: ");
        puts(movies[i].name);
        printf("\nDescription: ");
        puts(movies[i].description);
        printf("Start Time: ");
        puts(movies[i].start_time);
        printf("Duration: %d minutes\n", movies[i].duration);
        printf("Reserved Seats: %d\n", movies[i].num_reserved_seats);
        printf("\n");
    }
}

void display_reservations(movie_t movies[], int num_movies) {
    if (num_movies == 0) {
        printf("No movies available.\n");
        return;
    }

    char movie_name[50];
    printf("Enter the name of the movie to display reservations: ");
    fflush(stdin);
    gets(movie_name);

    int found = 0;
    for (int i = 0; i < num_movies; i++) {
        if (strcmpi(movie_name, movies[i].name) == 0) {
            if (movies[i].num_reserved_seats == 0) {
                printf("No reservations available for this movie.\n");
                return;
            }

            printf("Reservations for Movie: ");
            puts(movies[i].name);
            printf("\n---------------------------\n");

            for (int j = 0; j < MAX_ROW; j++) {
                for(int k = 0; k < MAX_COLUMN; k++) {
                    printf("%d ", movies[i].reserved_seats[j][k]);
                }

                printf("\n");
            }
            printf("Total reserved seat: %d\n", movies[i].num_reserved_seats);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Movie not found.\n");
    }
}

void generate_revenue_report(movie_t movies[], int num_movies) {
    if (num_movies == 0) {
        printf("No movies available.\n");
        return;
    }

    printf("Revenue Report\n");
    printf("--------------\n");

    double total_revenue = 0.0;

    for (int i = 0; i < num_movies; i++) {
        double movie_revenue = movies[i].num_reserved_seats * TICKET_PRICE;
        printf("Movie: ");
        puts(movies[i].name);
        printf("\nReserved Seats: %d\n", movies[i].num_reserved_seats);
        printf("Revenue: $%.2lf\n", movie_revenue);
        printf("\n");

        total_revenue += movie_revenue;
    }

    printf("Total Revenue: $%.2lf\n\n", total_revenue);
}
