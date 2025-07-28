# Job-Seeking-Application
The Job Matching Application is a command-line tool built using C that helps job seekers and job providers find suitable matches based on their preferences. This README file provides an overview of the application, installation instructions, and usage guidelines.
## Features

- **Job Seeker Features:**
  - Job seekers can create a profile by entering their personal information, skills, and job preferences.
  - The application provides a list of job providers that match the job seeker's preferences, based on the available job listings.
  - Job seekers can view detailed information about each job provider and apply for jobs.

- **Job Provider Features:**
  - Job providers can create a profile by entering their company information, job listings, and desired candidate criteria.
  - The application suggests a list of job seekers who match the job provider's requirements.
  - Job providers can view detailed profiles of job seekers and initiate contact for further discussion.

## Installation

1. Compile the source code:   
   gcc job_matching_app.c -o main
3. Run the application:
   ./main

## Usage

Upon launching the application, you will be presented with a menu that allows you to choose whether you want to use the application as a job seeker or a job provider. Follow the on-screen prompts and enter the required information to create your profile.

For job seekers:
- Enter your personal information, skills, and job preferences.
- View the list of job providers that match your preferences.
- Select a job provider to view detailed information and apply for jobs.

For job providers:
- Enter your company information and desired candidate criteria.
- Add job listings with relevant details i.e weights and required score to attain that job.
- View the list of job seekers that match your requirements.
- Select a job seeker to view their detailed profile and initiate contact.
Remember to save any changes or updates to your profile before exiting the application.

## Acknowledgements
We would like to thank the following resources for their valuable contributions and inspiration:
- Linkedin(One of the popular website to find job providers based on the required constraint)
- https://www.learn-c.org/en/Dynamic_allocation 
- https://www.csir.res.in/intellectual-property-directorate-ipd-0   (Here in this website we utilised the data flow that was happening between servers and application through filtering process. We tried to implement the same using csv file and structure filtration).
Feel free to add any additional sections or information that you think would be relevant to your project.
