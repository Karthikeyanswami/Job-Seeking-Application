#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_USERS 100
#define FILE_NAME "user.csv"
#define MAX_EMPLOYEES 100
#define MAX_LINE_LENGTH 256
#define MAX_LENGTH 1000

typedef struct {
  int employeecode;
  char username[MAX_LENGTH];
  char password[MAX_LENGTH];
  char email[MAX_LENGTH];
  char dob[MAX_LENGTH];
  char phoneNumber[MAX_LENGTH];
  char address[MAX_LENGTH];
} User;

typedef struct {
  char username[MAX_LENGTH];
  char password[MAX_LENGTH];
} user_pass;

typedef struct {
  char code[MAX_LENGTH];
  char password[MAX_LENGTH];
} Admin;

Admin admin;

struct Employee_all {
  int empid;
  char education[50];
  char job_preference[50];
  char company_preference[50];
  char pro_skill1[50];
  char pro_skill2[50];
  char pro_skill3[50];
  char pro_skill4[50];
  char pro_skill5[50];
  int pro_score;
  char location[50];
  int workex;
  char lang1[50];
  char lang2[50];
  char lang3[50];
  char salary[50];
};

struct JobProvider {
  char jobcode[MAX_LENGTH];
  char companycode[MAX_LENGTH];
  char companyname[MAX_LENGTH];
  int vacantseats;
  float weight1;
  float weight2;
  float weight3;
  float weight4;
  float weight5;
  // float weight6;
  float requiredscore;
  char job_title[MAX_LENGTH];
  char location[MAX_LENGTH];
  char salary[MAX_LENGTH];
};

// fprintf(file, "Username,Password,Email,DOB,Phone Number,Address\n"); //
// Header row

struct JobProvider *filterJobProviderByPreference(const char *jobPreference,
                                                  int *numMatches) {
  FILE *file = fopen("providerdetails.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  char line[MAX_LENGTH];
  fgets(line, sizeof(line), file); // Skip the header line

  // Define a temporary array to store the filtered data
  int capacity = 100; // Initial capacity
  struct JobProvider *filteredData =
      malloc(capacity * sizeof(struct JobProvider));
  *numMatches = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract the fields from line using sscanf
    char jobcode[MAX_LENGTH];
    char companycode[MAX_LENGTH];
    char companyname[MAX_LENGTH];
    int vacant;
    float weight1;
    float weight2;
    float weight3;
    float weight4;
    float weight5;
    int reqscore;
    char job_title[MAX_LENGTH];
    char location[MAX_LENGTH];
    char salary[MAX_LENGTH];

    if (sscanf(line,
               "%[^,],%[^,],%[^,],%d,%f,%f,%f,%f,%f,%d,%[^,],%[^,],%[^,\n]",
               jobcode, companycode, companyname, &vacant, &weight1, &weight2,
               &weight3, &weight4, &weight5, &reqscore, job_title, location,
               salary) != 13) {
      continue; // Skip incomplete lines
    }

    // Check the condition and filter the data
    // printf("%d ans : ",(strcmp(job_title, jobPreference)) );
    // job_title[strcspn(job_title, "\n")] = '\0';
    if (strcmp(job_title, jobPreference) == 0) {
      // Increase the size of the filteredData array if needed
      if (*numMatches >= capacity) {
        capacity *= 2; // Double the capacity
        struct JobProvider *temp =
            realloc(filteredData, capacity * sizeof(struct JobProvider));
        if (temp == NULL) {
          printf("Memory allocation failed.\n");
          free(filteredData);
          fclose(file);
          return NULL;
        }
        filteredData = temp;
      }

      // Store the field values in the filteredData array
      strcpy(filteredData[*numMatches].jobcode, jobcode);
      strcpy(filteredData[*numMatches].companyname, companyname);
      strcpy(filteredData[*numMatches].companycode, companycode);
      filteredData[*numMatches].vacantseats = vacant;
      filteredData[*numMatches].weight1 = weight1;
      filteredData[*numMatches].weight2 = weight2;
      filteredData[*numMatches].weight3 = weight3;
      filteredData[*numMatches].weight4 = weight4;
      filteredData[*numMatches].weight5 = weight5;
      filteredData[*numMatches].requiredscore = reqscore;
      strcpy(filteredData[*numMatches].job_title, job_title);
      strcpy(filteredData[*numMatches].location, location);
      strcpy(filteredData[*numMatches].salary, salary);

      (*numMatches)++;
    }
  }

  fclose(file);

  // Return the filtered data
  return filteredData;
}

struct JobProvider *filterJobProviderByLocation(const char *location1,
                                                int *numMatches) {
  FILE *file = fopen("providerdetails.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  char line[MAX_LENGTH];
  fgets(line, sizeof(line), file); // Skip the header line

  // Define a temporary array to store the filtered data
  int capacity = 100; // Initial capacity
  struct JobProvider *filteredData =
      malloc(capacity * sizeof(struct JobProvider));
  *numMatches = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract the fields from line using sscanf
    char jobcode[MAX_LENGTH];
    char companycode[MAX_LENGTH];
    char companyname[MAX_LENGTH];
    int vacant;
    float weight1;
    float weight2;
    float weight3;
    float weight4;
    float weight5;
    int reqscore;
    char job_title[MAX_LENGTH];
    char location[MAX_LENGTH];
    char salary[MAX_LENGTH];

    if (sscanf(line,
               "%[^,],%[^,],%[^,],%d,%f,%f,%f,%f,%f,%d,%[^,],%[^,],%[^,\n]",
               jobcode, companycode, companyname, &vacant, &weight1, &weight2,
               &weight3, &weight4, &weight5, &reqscore, job_title, location,
               salary) != 13) {
      continue; // Skip incomplete lines
    }

    // Check the condition and filter the data
    // printf("%d ans : ",(strcmp(job_title, jobPreference)) );
    job_title[strcspn(job_title, "\n")] = '\0';
    if (strcmp(location, location1) == 0) {
      // Increase the size of the filteredData array if needed
      if (*numMatches >= capacity) {
        capacity *= 2; // Double the capacity
        struct JobProvider *temp =
            realloc(filteredData, capacity * sizeof(struct JobProvider));
        if (temp == NULL) {
          printf("Memory allocation failed.\n");
          free(filteredData);
          fclose(file);
          return NULL;
        }
        filteredData = temp;
      }

      // Store the field values in the filteredData array
      strcpy(filteredData[*numMatches].jobcode, jobcode);
      strcpy(filteredData[*numMatches].companyname, companyname);
      strcpy(filteredData[*numMatches].companycode, companycode);
      filteredData[*numMatches].vacantseats = vacant;
      filteredData[*numMatches].weight1 = weight1;
      filteredData[*numMatches].weight2 = weight2;
      filteredData[*numMatches].weight3 = weight3;
      filteredData[*numMatches].weight4 = weight4;
      filteredData[*numMatches].weight5 = weight5;
      filteredData[*numMatches].requiredscore = reqscore;
      strcpy(filteredData[*numMatches].job_title, job_title);
      strcpy(filteredData[*numMatches].location, location);
      strcpy(filteredData[*numMatches].salary, salary);

      (*numMatches)++;
    }
  }

  fclose(file);

  // Return the filtered data
  return filteredData;
}

struct JobProvider *filterJobProviderByName(const char *name1,
                                            int *numMatches) {
  FILE *file = fopen("providerdetails.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  char line[MAX_LENGTH];
  fgets(line, sizeof(line), file); // Skip the header line

  // Define a temporary array to store the filtered data
  int capacity = 100; // Initial capacity
  struct JobProvider *filteredData =
      malloc(capacity * sizeof(struct JobProvider));
  *numMatches = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract the fields from line using sscanf
    char jobcode[MAX_LENGTH];
    char companycode[MAX_LENGTH];
    char companyname[MAX_LENGTH];
    int vacant;
    float weight1;
    float weight2;
    float weight3;
    float weight4;
    float weight5;
    int reqscore;
    char job_title[MAX_LENGTH];
    char location[MAX_LENGTH];
    char salary[MAX_LENGTH];

    if (sscanf(line,
               "%[^,],%[^,],%[^,],%d,%f,%f,%f,%f,%f,%d,%[^,],%[^,],%[^,\n]",
               jobcode, companycode, companyname, &vacant, &weight1, &weight2,
               &weight3, &weight4, &weight5, &reqscore, job_title, location,
               salary) != 13) {
      continue; // Skip incomplete lines
    }

    // Check the condition and filter the data
    // printf("%d ans : ",(strcmp(job_title, jobPreference)) );
    // job_title[strcspn(job_title, "\n")] = '\0';
    if (strcmp(companyname, name1) == 0) {
      // Increase the size of the filteredData array if needed
      if (*numMatches >= capacity) {
        capacity *= 2; // Double the capacity
        struct JobProvider *temp =
            realloc(filteredData, capacity * sizeof(struct JobProvider));
        if (temp == NULL) {
          printf("Memory allocation failed.\n");
          free(filteredData);
          fclose(file);
          return NULL;
        }
        filteredData = temp;
      }

      // Store the field values in the filteredData array
      strcpy(filteredData[*numMatches].jobcode, jobcode);
      strcpy(filteredData[*numMatches].companyname, companyname);
      strcpy(filteredData[*numMatches].companycode, companycode);
      filteredData[*numMatches].vacantseats = vacant;
      filteredData[*numMatches].weight1 = weight1;
      filteredData[*numMatches].weight2 = weight2;
      filteredData[*numMatches].weight3 = weight3;
      filteredData[*numMatches].weight4 = weight4;
      filteredData[*numMatches].weight5 = weight5;
      filteredData[*numMatches].requiredscore = reqscore;
      strcpy(filteredData[*numMatches].job_title, job_title);
      strcpy(filteredData[*numMatches].location, location);
      strcpy(filteredData[*numMatches].salary, salary);
      (*numMatches)++;
    }
  }

  fclose(file);

  // Return the filtered data
  return filteredData;
}

struct JobProvider *filterJobProviderBycode(const char *code, int *numMatches) {
  FILE *file = fopen("providerdetails.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  char line[MAX_LENGTH];
  fgets(line, sizeof(line), file); // Skip the header line

  // Define a temporary array to store the filtered data
  int capacity = 100; // Initial capacity
  struct JobProvider *filteredData =
      malloc(capacity * sizeof(struct JobProvider));
  *numMatches = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract the fields from line using sscanf
    char jobcode[MAX_LENGTH];
    char companycode[MAX_LENGTH];
    char companyname[MAX_LENGTH];
    int vacant;
    float weight1;
    float weight2;
    float weight3;
    float weight4;
    float weight5;
    int reqscore;
    char job_title[MAX_LENGTH];
    char location[MAX_LENGTH];
    char salary[MAX_LENGTH];
    if (sscanf(line,
               "%[^,],%[^,],%[^,],%d,%f,%f,%f,%f,%f,%d,%[^,],%[^,],%[^,\n]",
               jobcode, companycode, companyname, &vacant, &weight1, &weight2,
               &weight3, &weight4, &weight5, &reqscore, job_title, location,
               salary) != 13) {
      continue; // Skip incomplete lines
    }

    // Check the condition and filter the data
    // printf("%d ans : ",(strcmp(job_title, jobPreference)) );
    // job_title[strcspn(job_title, "\n")] = '\0';
    if (strcmp(jobcode, code) == 0) {
      // Increase the size of the filteredData array if needed
      if (*numMatches >= capacity) {
        capacity *= 2; // Double the capacity
        struct JobProvider *temp =
            realloc(filteredData, capacity * sizeof(struct JobProvider));
        if (temp == NULL) {
          printf("Memory allocation failed.\n");
          free(filteredData);
          fclose(file);
          return NULL;
        }
        filteredData = temp;
      }

      // Store the field values in the filteredData array
      strcpy(filteredData[*numMatches].jobcode, jobcode);
      strcpy(filteredData[*numMatches].companyname, companyname);
      strcpy(filteredData[*numMatches].companycode, companycode);
      filteredData[*numMatches].vacantseats = vacant;
      filteredData[*numMatches].weight1 = weight1;
      filteredData[*numMatches].weight2 = weight2;
      filteredData[*numMatches].weight3 = weight3;
      filteredData[*numMatches].weight4 = weight4;
      filteredData[*numMatches].weight5 = weight5;
      filteredData[*numMatches].requiredscore = reqscore;
      strcpy(filteredData[*numMatches].job_title, job_title);
      strcpy(filteredData[*numMatches].location, location);
      strcpy(filteredData[*numMatches].salary, salary);
      (*numMatches)++;
    }
  }

  fclose(file);

  // Return the filtered data
  return filteredData;
}

void parseCSVLine(const char *line, User *user) {
  sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]", &user->employeecode,
         user->username, user->password, user->email, user->dob,
         user->phoneNumber, user->address);
}

struct JobProvider *filterJobProviderBySalary(const char *salary1,
                                              int *numMatches) {
  FILE *file = fopen("providerdetails.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  char line[MAX_LENGTH];
  fgets(line, sizeof(line), file); // Skip the header line

  // Define a temporary array to store the filtered data
  int capacity = 100; // Initial capacity
  struct JobProvider *filteredData =
      malloc(capacity * sizeof(struct JobProvider));
  *numMatches = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract the fields from line using sscanf
    char jobcode[MAX_LENGTH];
    char companycode[MAX_LENGTH];
    char companyname[MAX_LENGTH];
    int vacant;
    float weight1;
    float weight2;
    float weight3;
    float weight4;
    float weight5;
    int reqscore;
    char job_title[MAX_LENGTH];
    char location[MAX_LENGTH];
    char salary[MAX_LENGTH];
    if (sscanf(line,
               "%[^,],%[^,],%[^,],%d,%f,%f,%f,%f,%f,%d,%[^,],%[^,],%[^,\n]",
               jobcode, companycode, companyname, &vacant, &weight1, &weight2,
               &weight3, &weight4, &weight5, &reqscore, job_title, location,
               salary) != 13) {
      continue; // Skip incomplete lines
    }

    // Check the condition and filter the data
    // printf("%d ans : ",(strcmp(job_title, jobPreference)) );
    // job_title[strcspn(job_title, "\n")] = '\0';
    if (strcmp(salary, salary1) == 0) {
      // Increase the size of the filteredData array if needed
      if (*numMatches >= capacity) {
        capacity *= 2; // Double the capacity
        struct JobProvider *temp =
            realloc(filteredData, capacity * sizeof(struct JobProvider));
        if (temp == NULL) {
          printf("Memory allocation failed.\n");
          free(filteredData);
          fclose(file);
          return NULL;
        }
        filteredData = temp;
      }

      // Store the field values in the filteredData array
      strcpy(filteredData[*numMatches].jobcode, jobcode);
      strcpy(filteredData[*numMatches].companyname, companyname);
      strcpy(filteredData[*numMatches].companycode, companycode);
      filteredData[*numMatches].vacantseats = vacant;
      filteredData[*numMatches].weight1 = weight1;
      filteredData[*numMatches].weight2 = weight2;
      filteredData[*numMatches].weight3 = weight3;
      filteredData[*numMatches].weight4 = weight4;
      filteredData[*numMatches].weight5 = weight5;
      filteredData[*numMatches].requiredscore = reqscore;
      strcpy(filteredData[*numMatches].job_title, job_title);
      strcpy(filteredData[*numMatches].location, location);
      strcpy(filteredData[*numMatches].salary, salary);
      (*numMatches)++;
    }
  }

  fclose(file);

  // Return the filtered data
  return filteredData;
}

struct Employee_all *filterJobSeekerByPreference(const char *jobPreference,
                                                 int *numMatches) {
  FILE *file = fopen("seekerdetails.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  char line[MAX_LENGTH];
  // fgets(line, sizeof(line), file); // Skip the header line

  // Define a temporary array to store the filtered data
  int capacity = 10; // Initial capacity
  struct Employee_all *filteredData =
      malloc(capacity * sizeof(struct Employee_all));
  *numMatches = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Extract the fields from line using sscanf
    int empid;
    char education[50];
    char job_preference[50];
    char company_preference[50];
    char pro_skill1[50];
    char pro_skill2[50];
    char pro_skill3[50];
    char pro_skill4[50];
    char pro_skill5[50];
    int pro_score;
    char location[50];
    int workex;
    char lang1[50];
    char lang2[50];
    char lang3[50];
    char salary[50];

    if (sscanf(line,
               "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%d,"
               "%[^,],%[^,],%[^,],%[^,\n]",
               &empid, education, job_preference, company_preference,
               pro_skill1, pro_skill2, pro_skill3, pro_skill4, pro_skill5,
               &pro_score, location, &workex, lang1, lang2, lang3,
               salary) != 16) {
      continue; // Skip incomplete lines
    }

    // Check the condition and filter the data
    if (strcmp(job_preference, jobPreference) == 0) {
      // Increase the size of the filteredData array if needed
      if (*numMatches >= capacity) {
        capacity *= 2; // Double the capacity
        struct Employee_all *temp =
            realloc(filteredData, capacity * sizeof(struct Employee_all));
        if (temp == NULL) {
          printf("Memory allocation failed.\n");
          free(filteredData);
          fclose(file);
          return NULL;
        }
        filteredData = temp;
      }

      // Store the field values in the filteredData array
      filteredData[*numMatches].empid = empid;
      strcpy(filteredData[*numMatches].education, education);
      strcpy(filteredData[*numMatches].job_preference, job_preference);
      strcpy(filteredData[*numMatches].company_preference, company_preference);
      strcpy(filteredData[*numMatches].pro_skill1, pro_skill1);
      strcpy(filteredData[*numMatches].pro_skill2, pro_skill2);
      strcpy(filteredData[*numMatches].pro_skill3, pro_skill3);
      strcpy(filteredData[*numMatches].pro_skill4, pro_skill4);
      strcpy(filteredData[*numMatches].pro_skill4, pro_skill4);
      strcpy(filteredData[*numMatches].pro_skill5, pro_skill5);
      filteredData[*numMatches].pro_score = pro_score;
      strcpy(filteredData[*numMatches].location, location);
      filteredData[*numMatches].workex = workex;
      strcpy(filteredData[*numMatches].lang1, lang1);
      strcpy(filteredData[*numMatches].lang2, lang2);
      strcpy(filteredData[*numMatches].lang3, lang3);
      strcpy(filteredData[*numMatches].salary, salary);
      (*numMatches)++;
    }
  }

  fclose(file);

  // Return the filtered data
  return filteredData;
}

double calculateScore(struct Employee_all *employee,
                      struct JobProvider *provider) {
  // Assign weights to different attributes
  double proweight = provider->weight1;
  double workex = provider->weight2;
  double lang = provider->weight3;

  float score = 0.0;

  // Check if employee's attributes match the preferences
  score = (proweight * (employee->pro_score)) + (workex * (employee->workex));

  return score;
}

void saveMatchingEmployees(const char *jobCode, int employeeCode) {
  FILE *file = fopen("matching_employees.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
  }

  // Check if the record already exists
  char line[MAX_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    char savedJobCode[MAX_LENGTH];
    int savedEmployeeCode;
    if (sscanf(line, "%[^,],%d\n", savedJobCode, &savedEmployeeCode) == 2) {
      if (strcmp(savedJobCode, jobCode) == 0 &&
          savedEmployeeCode == employeeCode) {
        fclose(file);
        return; // Duplicate record found, no need to append
      }
    }
  }

  fclose(file);

  // Append the record to the file
  file = fopen("matching_employees.csv", "a");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
  }

  fprintf(file, "%s,%d\n", jobCode, employeeCode);
  fclose(file);
}

/*void saveMatchingProviders(const char *jobCode, int employeeCode) {
  FILE *file = fopen("matching_providers.csv", "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
  }

  // Check if the record already exists
  char line[MAX_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    char savedJobCode[MAX_LENGTH];
    int savedEmployeeCode;
    if (sscanf(line, "%d,%[^,\n]", &savedEmployeeCode, savedJobCode) == 2) {
      if (strcmp(savedJobCode, jobCode) == 0 &&
          savedEmployeeCode == employeeCode) {
        fclose(file);
        return; // Duplicate record found, no need to append
      }
    }
  }

  fclose(file);

  // Append the record to the file
  file = fopen("matching_providers.csv", "a");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
  }

  fprintf(file, "%d,%s\n", employeeCode, jobCode);
  fclose(file);
}*/

void adminSignup() {
  FILE *file = fopen("admin_credentials.csv", "a");

  if (file == NULL) {
    printf("Failed to open the file for writing.\n");
    return;
  }

  printf("\nAdmin Signup:\n");
  printf("Company Code: ");
  fgets(admin.code, sizeof(admin.code), stdin);
  admin.code[strcspn(admin.code, "\n")] =
      '\0'; // Remove trailing newline character

  printf("Password: ");
  fgets(admin.password, sizeof(admin.password), stdin);
  admin.password[strcspn(admin.password, "\n")] =
      '\0'; // Remove trailing newline character

  fprintf(file, "%s,%s\n", admin.code, admin.password);
  fclose(file);

  printf("Admin signup successful!\n");
}

int adminLogin() {
  char code[MAX_LENGTH];
  char password[MAX_LENGTH];

  printf("\nAdmin Login:\n");
  printf("Company Code: ");
  fgets(code, sizeof(code), stdin);
  code[strcspn(code, "\n")] = '\0'; // Remove trailing newline character

  printf("Password: ");
  fgets(password, sizeof(password), stdin);
  password[strcspn(password, "\n")] = '\0'; // Remove trailing newline character

  FILE *file = fopen("admin_credentials.csv", "r");

  if (file == NULL) {
    printf("Failed to open the file for reading.\n");
    return 0; // Login failed
  }

  char storedCode[MAX_LENGTH];
  char storedPassword[MAX_LENGTH];
  int isLoggedIn = 0;

  char line[MAX_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%[^,],%s", storedCode, storedPassword);

    // Verify the company code and password
    if (strcmp(storedCode, code) == 0 &&
        strcmp(storedPassword, password) == 0) {

      isLoggedIn = 1;
    }
  }

  fclose(file);

  return isLoggedIn;
}
int generateUserCode() {
  // Generate a random 5-digit user code
  return (rand() % 100000);
}

int validatePhoneNumber(char phoneNumber[]) {
  int length = strlen(phoneNumber);

  // Check if the length is valid
  if (length != 10)
    return 1; // Invalid length

  // Check if all characters are digits
  for (int i = 0; i < length; i++) {
    if (!isdigit(phoneNumber[i]))
      return 2; // Non-digit character found
  }

  // Phone number is valid
  return (0); // Valid phone number
}

int checkUsernameExists(const char *username) {
  FILE *file = fopen("username.csv", "r");
  if (file == NULL) {
    printf("Error opening file!\n");
    return -1;
  }

  char line[MAX_LENGTH];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0'; // Remove trailing newline character

    if (strcmp(line, username) == 0) {
      fclose(file);
      return 1; // Username exists in the file
    }
  }

  fclose(file);
  return 0; // Username does not exist in the file
}

void writeUseridToFile(int emp_id) {
  FILE *file = fopen("userid.csv", "a");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  fprintf(file, "%d", emp_id);

  fprintf(file, "\n");
  fclose(file);
}

void writeUsernameToFile(char username[]) {
  FILE *file = fopen("username.csv", "a");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  fprintf(file, "%s", username);
  // fprintf(file," ");

  fprintf(file, "\n");
  fclose(file);
}

void writeUsersToFile(User users[], int numUsers) {
  FILE *file = fopen(FILE_NAME, "a");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  // fprintf(file, "Username,Password,Email,DOB,Phone Number,Address\n"); //
  // Header row

  for (int i = 0; i < numUsers; i++) {
    if (users[i].employeecode != 0 && *users[i].username != NULL &&
        *users[i].password != NULL && *users[i].email != NULL &&
        *users[i].dob != NULL && *users[i].phoneNumber != NULL &&
        *users[i].address != NULL) {

      fprintf(file, "%d,%s,%s,%s,%s,%s,%s\n", users[i].employeecode,
              users[i].username, users[i].password, users[i].email,
              users[i].dob, users[i].phoneNumber, users[i].address);
    }
  }

  fclose(file);
}

int findUserIndex(user_pass users1[], int numUsers, char username[]) {
  for (int i = 0; i < numUsers; i++) {
    // printf("%s \n",users1[i].password);
    // printf("%s\n",username);
    if (strcmp(users1[i].username, username) == 0) {
      return i;
    }
  }
  return -1;
}

void writeUsersToFile1(user_pass users1[], int numUsers) {
  FILE *file = fopen("user_pass.csv", "w");
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }

  // fprintf(file, "Username,Password,Email,DOB,Phone Number,Address\n"); //
  // Header row

  for (int i = 0; i < numUsers; i++) {
    fprintf(file, "%s,%s\n", users1[i].username, users1[i].password);
  }

  fclose(file);
}

// JOB SEEKER DETAILS
#define MAX_LANGUAGES 3
#define MAX_PROGRAMMING_LANGUAGES 5
#define MAX_STRING_LENGTH 100

struct JobSeeker {
  char employee_id[MAX_LENGTH];
  char education[MAX_STRING_LENGTH];
  char job_preference[MAX_STRING_LENGTH];
  char company_preference[MAX_STRING_LENGTH];
  char programming_languages[MAX_PROGRAMMING_LANGUAGES][MAX_STRING_LENGTH];
  int score;
  char location[MAX_STRING_LENGTH];
  int experience;
  char languages[MAX_LANGUAGES][MAX_STRING_LENGTH];
  char salary[50];
};

int checkUseridExists(const char *username) {
  FILE *file = fopen("userid.csv", "r");
  if (file == NULL) {
    printf("Error opening file!\n");
    return -1;
  }

  char line[MAX_LENGTH];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0'; // Remove trailing newline character

    if (strcmp(line, username) == 0) {
      fclose(file);
      return 1; // Userid exists in the file
    }
  }

  fclose(file);
  return 0; // Username does not exist in the file
}

void saveJobSeekerDetails(struct JobSeeker *jobSeeker) {
  FILE *file = fopen("seekerdetails.csv", "a");
  if (file == NULL) {
    printf("Error: Unable to open the file.\n");
    return;
  }

  fprintf(file, "%s,%s,%s,%s,", jobSeeker->employee_id, jobSeeker->education,
          jobSeeker->job_preference, jobSeeker->company_preference);
  for (int i = 0; i < MAX_PROGRAMMING_LANGUAGES; i++) {
    fprintf(file, "%s,",
            jobSeeker->programming_languages[i][0] != '\0'
                ? jobSeeker->programming_languages[i]
                : "NaN");
  }
  fprintf(file, "%d,", jobSeeker->score);
  fprintf(file, "%s,%d,", jobSeeker->location, jobSeeker->experience);
  for (int i = 0; i < MAX_LANGUAGES; i++) {
    fprintf(file, "%s,",
            jobSeeker->languages[i][0] != '\0' ? jobSeeker->languages[i]
                                               : "NaN");
  }
  fprintf(file, "%s,", jobSeeker->salary);
  fprintf(file, "\n");

  fclose(file);
}

// SCORE
struct LanguageScore {
  char language[20];
  int score;
};

void read_csv(struct LanguageScore *scores, int max_scores) {
  FILE *file = fopen("language_score.csv", "r");
  if (file != NULL) {
    char line[50];
    fgets(line, sizeof(line), file); // Skip header row

    int i = 0;
    while (i < max_scores && fgets(line, sizeof(line), file) != NULL) {
      char *token = strtok(line, ",");
      strcpy(scores[i].language, token);
      token = strtok(NULL, ",");
      scores[i].score = atoi(token);
      i++;
    }

    fclose(file);
  } else {
    printf("Error opening the CSV file.\n");
  }
}

int main() {
  printf("----------Welcome To The Program--------\n");
  printf("1.Admin\n");
  printf("2.User\n");
  printf("Enter your choice : ");
  int ch;
  scanf("%d", &ch);
  printf("\n------------------------------------------\n");

  if (ch == 1) {
    int choice;
    int isLoggedIn = 0;

    printf("\n--- Admin Login Page ---\n");

    printf("\n1. Admin Signup\n");
    printf("2. Admin Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear the newline character from the input buffer

    switch (choice) {
    case 1:
      adminSignup();
      break;
    case 2:
      isLoggedIn = adminLogin();
      if (isLoggedIn) {
        printf("Admin login successful!\n");
        // this part of code is for jobprovider who want to see the candidates
        // list
        printf("========================================================\n");
        printf("\n");
        char input[MAX_LENGTH];
        char input1[100];
        printf("Re-enter the Company Code :");
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = '\0';
        printf("Enter the Job Preference by which you want to filter the job "
               "seekers: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        const char *jobPreference = input;
        int numMatches1;
        struct Employee_all *matches1 =
            filterJobSeekerByPreference(jobPreference, &numMatches1);

        if (matches1 == NULL) {
          printf("No matching job seekers found.\n");
        } else {
          printf("-------Matching Job seekers:-------\n");
          if (numMatches1 == 0) {
            printf("No matching Job Seekers found!\n");
          }
          for (int i = 0; i < numMatches1; i++) {
            printf("Emp Code: %d\n", matches1[i].empid);
            printf("Job preference: %s\n", matches1[i].job_preference);
            printf("Company preference: %s\n", matches1[i].company_preference);
            printf("Programming Skill 1: %s\n", matches1[i].pro_skill1);
            printf("Programming Skill 2: %s\n", matches1[i].pro_skill2);
            printf("Programming Skill 3: %s\n", matches1[i].pro_skill3);
            printf("Programming Skill 4: %s\n", matches1[i].pro_skill4);
            printf("Programming Skill 5: %s\n", matches1[i].pro_skill5);
            printf("Location: %s\n", matches1[i].location);
            printf("Language1: %s\n", matches1[i].lang1);
            printf("Language2: %s\n", matches1[i].lang2);
            printf("Language3: %s\n", matches1[i].lang3);
            printf("Expected Salary : %s\n", matches1[i].salary);
            printf("\n");
          }
          printf("-------SCORING--------\n");

          const char *code = "JC001";
          int nummatch;
          struct JobProvider *provider =
              filterJobProviderBycode(code, &nummatch);
          if (provider != NULL) {
            for (int i = 0; i < numMatches1; i++) {
              double score = calculateScore(&matches1[i], provider);

              printf("Score: %0.4f, Required Score: %0.4f\n", score,
                     provider->requiredscore); // Debugging statement
              if (score >= (float)provider->requiredscore) {
                printf("!!!Potential Candidate : \n");
                printf("Company Code : %s ,Job Name: %s, Employee Code: %d\n",
                       input1, input, matches1[i].empid);
                int match = matches1[i].empid;
                saveMatchingEmployees(provider->jobcode, matches1[i].empid);

                User users[100];
                int numUsers = 0;

                FILE *file = fopen("user.csv", "r");
                if (file == NULL) {
                  printf("Error opening file!\n");
                  return 1;
                }

                while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
                              &users[numUsers].employeecode,
                              users[numUsers].username,
                              users[numUsers].password, users[numUsers].email,
                              users[numUsers].dob, users[numUsers].phoneNumber,
                              users[numUsers].address) == 7) {
                  numUsers++;
                }

                fclose(file);

                printf("\n");
                // Search for the user with the given ID
                int i;
                for (i = 0; i < numUsers; i++) {
                  if (users[i].employeecode == match) {
                    printf("---User Details----\n");
                    printf("ID: %d\n", users[i].employeecode);
                    printf("Username: %s\n", users[i].username);
                    printf("EMAIL ID : %s\n", users[i].email);
                    printf("DATE OF BIRTH : %s\n", users[i].dob);
                    printf("Address: %s\n", users[i].address);
                    printf("Phone Number: %s\n", users[i].phoneNumber);
                    break;
                  }
                }

                printf("\n");
              } else {
                printf("Employee Code : %d Did Not meet the minimum score\n",
                       matches1[i].empid);
                printf("\n");
              }
            }

          } else {
            printf("No matching job provider found.\n");
          }
        }
      } else {
        printf("Admin login failed.\n");
      }
      break;
    case 3:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice.\n");
    }

  }

  else if (ch == 2) {
    printf("\n--- User Login Page ---\n");
    User users[MAX_USERS];
    user_pass users1[MAX_USERS];
    time_t t1;
    srand(&t1);
    int numUsers = 0;
    // Load existing user data from CSV file
    FILE *file = fopen("user_pass.csv", "r");
    if (file != NULL) {
      char line[MAX_LENGTH];
      // fgets(line, sizeof(line), file); // Skip the header row

      while (fgets(line, sizeof(line), file) != NULL) {

        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");

        if (username != NULL && password != NULL) {

          strncpy(users1[numUsers].username, username, MAX_LENGTH);
          strncpy(users1[numUsers].password, password, MAX_LENGTH);
        }
        numUsers++;
      }

      fclose(file);
    }

    // Sign up or Login
    char input[MAX_LENGTH];
    printf("1. Sign up\n");
    printf("2. Login\n");
    printf("Enter your choice: ");
    char ch = scanf("%c", &ch);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "1") == 0) {
      // Sign up
      printf("Here is your  employee id :");
      int res = generateUserCode();
      printf("%d\n", res);
      writeUseridToFile(res);
      users[numUsers].employeecode = res;

      printf("Enter your username: ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      char input1[MAX_LENGTH];

      int usernameExists = checkUsernameExists(input);
      while (usernameExists == 1) {
        printf("Username already exists.");
        printf("Please enter a different username: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        usernameExists = checkUsernameExists(input);
      }

      if (usernameExists == -1) {
        printf("Error occurred while checking username existence.\n");
      } else {
        printf("Username is available!\n");
        // printf("%s\n",input);
        input[strcspn(input, "\n")] = '\0';
        printf("Re-Enter the username : ");
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = '\0';
        strncpy(users[numUsers].username, input, MAX_LENGTH);
        strncpy(users1[numUsers].username, input, MAX_LENGTH);

        writeUsernameToFile(input);
      }

      printf("Enter your password: ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      strncpy(users[numUsers].password, input, MAX_LENGTH);
      printf("Re-Enter your password : ");
      fgets(input1, sizeof(input1), stdin);
      input1[strcspn(input1, "\n")] = '\0';
      strncpy(users1[numUsers].password, input, MAX_LENGTH);

      printf("Enter your email: ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      strncpy(users[numUsers].email, input, MAX_LENGTH);

      printf("Enter your date of birth (DOB): ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      strncpy(users[numUsers].dob, input, MAX_LENGTH);

      int validationStatus;

      while (validationStatus != 0) {
        printf("Enter a phone number (10 digits): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline character

        validationStatus = validatePhoneNumber(input);

        if (validationStatus == 1) {
          printf("Invalid phone number length! Please try again.\n");
        } else if (validationStatus == 2) {
          printf("Invalid phone number format! Please try again.\n");
        }
      }
      input[strcspn(input, "\n")] = '\0';
      strncpy(users[numUsers].phoneNumber, input, MAX_LENGTH);
      printf("Valid phone number!\n");

      printf("Enter your address: ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';
      strncpy(users[numUsers].address, input, MAX_LENGTH);

      numUsers++;

      writeUsersToFile(users, numUsers);
      writeUsersToFile1(users1, numUsers);

      printf("Sign up successful!\n");

    }

    else if (strcmp(input, "2") == 0) {
      // Login
      printf("Enter your username: ");
      fgets(input, sizeof(input), stdin);
      input[strcspn(input, "\n")] = '\0';

      int userIndex = findUserIndex(users1, numUsers, input);

      if (userIndex != -1) {
        printf("Enter your password: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        char str[200];
        strcpy(str, users1[userIndex].password);
        str[strcspn(str, "\n")] = '\0';
        if (strcmp(str, input) == 0) {
          printf("Login successful!\n");
          printf("Welcome, %s!\n", users[userIndex].username);
          // Perform actions after successful login
          struct JobSeeker jobSeeker;

          printf("=====================================\n");
          printf("\n");
          printf("--- Job Seeker Details ---\n");
          printf("Enter Job Seeker details:\n");
          printf("Employee ID: ");
          scanf("%[^\n]%*c", jobSeeker.employee_id);

          int res = checkUseridExists(jobSeeker.employee_id);

          if (res == 0) {
            printf("Invalid employee id\n");
            printf("EXITING....");

          }

          else if (res == 1) {

            printf("Education: ");
            scanf("%[^\n]%*c", jobSeeker.education);

            printf("Job Preference: ");
            scanf("%[^\n]%*c", jobSeeker.job_preference);

            printf("Company Preference: ");
            scanf("%[^\n]%*c", jobSeeker.company_preference);

            int score = 0;
            int max_scores = 22;
            struct LanguageScore scores[max_scores];
            printf(
                "Programming Languages (up to %d, separated by new lines):\n",
                MAX_PROGRAMMING_LANGUAGES);
            for (int i = 0; i < MAX_PROGRAMMING_LANGUAGES; i++) {
              fgets(jobSeeker.programming_languages[i], MAX_STRING_LENGTH,
                    stdin);
              read_csv(scores, 22);
              jobSeeker.programming_languages
                  [i][strlen(jobSeeker.programming_languages[i]) - 1] = '\0';
              if (jobSeeker.programming_languages[i][0] == '\0') {
                strcpy(jobSeeker.programming_languages[i], "NaN");
              }
            }

            for (int i = 0; i < 5; i++) {
              for (int j = 0; j < 22; j++) {
                if (strcmp(jobSeeker.programming_languages[i],
                           scores[j].language) == 0) {
                  score += scores[j].score;
                  break;
                }

                if (jobSeeker.programming_languages[i][0] == '\0') {
                  score += 0;
                }
              }
            }
            jobSeeker.score = score;

            printf("Location: ");
            scanf("%[^\n]%*c", jobSeeker.location);

            printf("Experience (in years): ");
            scanf("%d%*c", &(jobSeeker.experience));

            printf("Languages (up to %d, separated by new lines):\n",
                   MAX_LANGUAGES);
            for (int i = 0; i < MAX_LANGUAGES; i++) {
              fgets(jobSeeker.languages[i], MAX_STRING_LENGTH, stdin);
              jobSeeker.languages[i][strlen(jobSeeker.languages[i]) - 1] = '\0';
              if (jobSeeker.languages[i][0] == '\0') {
                strcpy(jobSeeker.languages[i], "NaN");
              } else {
                continue;
              }
            }

            printf("Salary: ");
            scanf("%[^\n]%*c", jobSeeker.salary);

            saveJobSeekerDetails(&jobSeeker);
            printf("Job Seeker details saved to file.\n");

            printf("\n--- Job Seeker Details ---\n");
            printf("Loading Job Seeker details from file...\n");

            // loadJobSeekerDetails(&jobSeeker);

            printf("Employee ID: %s\n", jobSeeker.employee_id);
            printf("Education: %s\n", jobSeeker.education);
            printf("Job Preference: %s\n", jobSeeker.job_preference);
            printf("Company Preference: %s\n", jobSeeker.company_preference);
            printf("Programming Languages: ");
            for (int i = 0; i < MAX_PROGRAMMING_LANGUAGES; i++) {
              printf("%s ", jobSeeker.programming_languages[i]);
            }
            printf("\n");
            printf("Location: %s\n", jobSeeker.location);
            printf("Experience: %d years\n", jobSeeker.experience);
            printf("Languages: ");
            for (int i = 0; i < MAX_LANGUAGES; i++) {
              printf("%s ", jobSeeker.languages[i]);
            }
            printf("\n");
            printf("Expected Salary : %s\n", jobSeeker.salary);

            printf("-------------------------------------------\n");
            printf("\n");
            while (1) {
              printf("Enter the compulsory constraint\n");
              printf("1.Job Preference   2. Company Name   3.Location   "
                     "4.Expected Salary\n");
              printf("Enter any other number to exit\n");
              printf("Enter your choice : ");
              int ch;
              scanf("%d", &ch);

              if (ch == 1) {
                char input1[100];
                printf("Enter your Job Preference : ");
                // fgets(input1, sizeof(input1), stdin);
                scanf("%s", input1);
                input1[strcspn(input1, "\n")] = '\0';
                const char *jobPreference1 = input1;
                int numMatches2;
                struct JobProvider *matches2 = filterJobProviderByPreference(
                    jobPreference1,
                    &numMatches2); // this stores the job description, weights
                                   // and all the values from the user.csv file.

                if (matches2 == NULL) {
                  printf("No matching job providers found.\n");
                } else {
                  printf("------Matching Job Providers:-------\n");
                  if (numMatches2 == 0) {
                    printf("No matching Job Providers found!");
                  }
                  for (int i = 0; i < numMatches2; i++) {
                    printf("Job Code: %s\n", matches2[i].jobcode);
                    printf("Company Code: %s\n", matches2[i].companycode);
                    printf("Company Name: %s\n", matches2[i].companyname);
                    printf("Job Title: %s\n", matches2[i].job_title);
                    printf("Location : %s\n", matches2[i].location);
                    printf("\n");
                  }
                }

                // Calculate scores for all employees and select the perfect
                // ones

              } else if (ch == 2) {
                char input[MAX_LENGTH];
                printf("Enter the Company Name : ");
                scanf("%s", input);
                const char *name = input;
                int numMatches2;
                struct JobProvider *matches2 = filterJobProviderByName(
                    name,
                    &numMatches2); // this stores the job description, weights
                                   // and all the values from the user.csv file.

                if (matches2 == NULL) {
                  printf("No matching job providers found.\n");
                } else {
                  printf("------Matching Job Providers:-------\n");
                  if (numMatches2 == 0) {
                    printf("No matching Job Providers found!");
                  }
                  for (int i = 0; i < numMatches2; i++) {
                    printf("Job Code: %s\n", matches2[i].jobcode);
                    printf("Company Code: %s\n", matches2[i].companycode);
                    printf("Company Name: %s\n", matches2[i].companyname);
                    printf("Job Title: %s\n", matches2[i].job_title);
                    printf("Location : %s\n", matches2[i].location);
                    printf("\n");
                  }
                }
              } else if (ch == 3) {
                char input[MAX_LENGTH];
                printf("Enter the Location : ");
                scanf("%s", input);
                input[strcspn(input, "\n")] = '\0';
                const char *location = input;
                int numMatches2;
                struct JobProvider *matches2 = filterJobProviderByLocation(
                    location,
                    &numMatches2); // this stores the job description, weights
                                   // and all the values from the user.csv file.

                if (matches2 == NULL) {
                  printf("No matching job providers found.\n");
                } else {
                  printf("-----Matching Job Providers:-----\n");
                  if (numMatches2 == 0) {
                    printf("No matching Job Providers found!");
                  }
                  for (int i = 0; i < numMatches2; i++) {
                    printf("Job Code: %s\n", matches2[i].jobcode);
                    printf("Company Code: %s\n", matches2[i].companycode);
                    printf("Company Name: %s\n", matches2[i].companyname);
                    printf("Job Title: %s\n", matches2[i].job_title);
                    printf("Location : %s\n", matches2[i].location);
                    printf("\n");
                  }
                }
              } else if (ch == 4) {
                char input1[100];
                printf("Enter your Expected Salary : ");
                // fgets(input1, sizeof(input1), stdin);
                scanf("%s", input1);
                input1[strcspn(input1, "\n")] = '\0';
                const char *jobPreference1 = input1;
                int numMatches2;
                struct JobProvider *matches2 = filterJobProviderBySalary(
                    jobPreference1,
                    &numMatches2); // this stores the job description, weights
                                   // and all the values from the user.csv file.

                if (matches2 == NULL) {
                  printf("No matching job providers found.\n");
                } else {
                  printf("------Matching Job Providers:-------\n");
                  if (numMatches2 == 0) {
                    printf("No matching Job Providers found!");
                  }
                  for (int i = 0; i < numMatches2; i++) {
                    printf("Job Code: %s\n", matches2[i].jobcode);
                    printf("Company Code: %s\n", matches2[i].companycode);
                    printf("Company Name: %s\n", matches2[i].companyname);
                    printf("Job Title: %s\n", matches2[i].job_title);
                    printf("Location : %s\n", matches2[i].location);
                    printf("Salary : %s\n", matches2[i].salary);
                    printf("\n");
                  }
                }

              }

              else {
                printf("Please enter a valid choice \n");
                printf("Exiting...");
                break;
              }
            }
          }

        } else {
          printf("Incorrect password.\n");
        }
      } else {
        printf("User not found.\n");
      }
    } else {
      printf("Invalid choice.\n");
    }
  }
  return 0;
}