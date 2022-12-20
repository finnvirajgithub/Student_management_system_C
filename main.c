#include<stdio.h>
#include<string.h>

struct s_course{
    char sc_name[50];
    char grade;
};

struct student{
    char name[20];
    char s_id[10];
    float gpa;
    int no_of_courses;
    char department[20];
    struct s_course many[10];
};

struct course{
    char course_id[10];
    char course_name[50];
    float credit_value;
};

void add_student(){
    system("cls");
    FILE * student_record;
    FILE * course_record;
    char command;
    struct student stu;
    struct course cou;
    float gpv=0,gpa=0,credit=0;
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   ADD STUDENT DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\n\t\t\t Enter your Name          :- ");
    scanf(" %[^\n]s",stu.name);
    printf("\n\t\t\t Enter your department    :- ");
    scanf(" %[^\n]s",stu.department);
    printf("\n\t\t\t Enter your University Id :- ");
    scanf(" %s",stu.s_id);

    printf("\n\n\t\t\t How many courses you followed/following? ");
    scanf("%d",&stu.no_of_courses);

    for(int i=0;i<stu.no_of_courses;i++){
        printf("\n\t\t\t\t Enter course %d    :- ",i+1);
        scanf(" %[^\n]s",stu.many[i].sc_name);
        printf("\n\t\t\t\t Enter your grade  :- ");
        scanf(" %c",&stu.many[i].grade);
    }
    for(int i=0;i<stu.no_of_courses;i++){
        course_record = fopen("Course record.txt","r");
        while(fread(&cou,sizeof(struct course),1,course_record)){
            if(strcmp(stu.many[i].sc_name,cou.course_name)==0){
                credit+=cou.credit_value;
                if(stu.many[i].grade=='A'){
                    gpv=cou.credit_value*4.0;
                }
                else if(stu.many[i].grade=='B'){
                    gpv=cou.credit_value*3.0;
                }
                else if(stu.many[i].grade=='C'){
                    gpv=cou.credit_value*2.5;
                }
                else if(stu.many[i].grade=='D'){
                    gpv=cou.credit_value*1.5;
                }
                else{
                    gpv=0;
                }
                break;
            }
        }
        gpa+=gpv;
        fclose(course_record);
    }
    stu.gpa=gpa/credit;
    student_record = fopen("Student record.txt","a");
    fwrite(&stu,sizeof(struct student),1,student_record);
    fclose(student_record);

    printf("\n\t\t Details succesfully saved!!!\n\n");

    printf("\n\t>> Add new record press 'n' \n");
    printf("\t>> To main menu press 'e'   \n");
    scanf(" %c",&command);

    while(command!='n' && command!='e' && command!='N' && command!='E'){
        printf("\t>> Add new record press 'n' \n");
        printf("\t>> To main menu press 'e'   \n");
        scanf(" %c",&command);
    }
    if(command=='n' || command=='N'){
        add_student();
    }
    else{
        main();
    }
}

void view_student(){
    system("cls");

    char command;
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   VIEW Student DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\n\n\t\t\t\t 1.All Student details (Press 1)\n");
    printf("\t\t\t\t 2.Search student details and edit (Press 2)\n\n\n");
    printf("\t\t>>To main menu press 'e' \n");
    scanf(" %c",&command);

    while(command!='1' && command!='2' && command!='e' && command!='E'){
        printf("\n\n\t\t\t\t 1.All Student (Press 1)\n");
        printf("\t\t\t\t 2.Search student details and edit (Press 2)\n\n\n");
        printf("\t>>To main menu press 'e'  \n");
        scanf(" %c",&command);
    }
    if(command=='1'){
        view_all_student();
    }
    else if(command=='2'){
        search_student();
    }
    else{
        main();
    }
}

void view_all_student(){
    system("cls");
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t  VIEW STUDENT DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    struct student stu;
    FILE *student_record;
    int found;
    char command;

    student_record=fopen("Student record.txt","r");
    if(student_record==NULL){
        printf("\n\t\tNo records available. please enter records.");
    }
    else{
        while(fread(&stu,sizeof(struct student),1,student_record)){
            found=1;
            printf("\n\t\t\t\tStudent name :- %s\n\n",stu.name);
            printf("\t\t\t\tstudent id :- %s\n\n",stu.s_id);
            printf("\t\t\t\tstudent department :- %s\n\n",stu.department);
            printf("\t\t\t\tcourses :- \n");

            for(int i=0;i<stu.no_of_courses;i++){
                printf("\t\t\t\t\t course %2d :- %s  -  %c\n",i+1,stu.many[i].sc_name,stu.many[i].grade);
            }

            printf("\n\t\t\t\tGPA :- %.2f",stu.gpa);
            printf("\n\n\t\t\t\t---------------------------------------\n");
        }
    }
    fclose(student_record);
    if(!found){
        printf("\t\t\t The record is not found \n\n");
    }

    printf("\n\n\t>> To Edit press 'y' \n");
    printf("\t>> To Edit press 'd' \n");
    printf("\t>> to back press 'b' \n");
    printf("\t>> To Main menu 'e'  \n");
    scanf(" %c",&command);

    while(command!='y' && command!='b' && command!='e' && command!='Y' && command!='B' && command!='E' && command!='d' && command!='D'){
        printf("\t>> To Edit press 'y' \n");
        printf("\t>> To Edit press 'd' \n");
        printf("\t>> to back press 'b' \n");
        printf("\t>> To Main menu 'e'  \n");
        scanf(" %c",&command);
    }
    if(command=='y' || command=='Y'){
        edit_student();
    }
    else if(command=='b' || command=='B'){
        view_student();
    }
    else if(command=='d' || command=='D'){
        delete_student();
    }
    else{
        main();
    }
}

void search_student(){
    system("cls");
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t  VIEW STUDENT DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    struct student stu;
    FILE *student_record;
    char input_id[15];
    int found;
    char command;

    printf("\t\t\t\tEnter University ID :- ");
    scanf(" %[^\n]s",input_id);
    student_record=fopen("Student record.txt","r");
    if(student_record==NULL){
        printf("\n\t\tNo records available. please enter records.");
    }
    else{
        while(fread(&stu,sizeof(struct student),1,student_record)){
            if(strcmp(input_id,stu.s_id)==0){
                found=1;
                printf("\n\t\t\t\tStudent name :- %s\n\n",stu.name);
                printf("\t\t\t\tstudent id :- %s\n\n",stu.s_id);
                printf("\t\t\t\tstudent department :- %s\n\n",stu.department);
                printf("\t\t\t\tcourses :- \n");

                for(int i=0;i<stu.no_of_courses;i++){
                    printf("\t\t\t\t\t course %d :- %s\n",i+1,stu.many[i].sc_name);
                    printf("\t\t\t\t\t Grade :- %c\n\n",stu.many[i].grade);
                }
                printf("\t\t\t\t GPA :- %.2f",stu.gpa);
            }
        }
        fclose(student_record);
        if(!found){
            printf("\t\t\t The record is not found \n\n");
        }
    }
    printf("\n\n\t>> To Edit press 'y' \n");
    printf("\t>> To delete record 'd' \n");
    printf("\t>> To View New record 'n' \n");
    printf("\t>> to back press 'b' \n");
    printf("\t>> To Main menu 'e'  \n");
    scanf(" %c",&command);

    while(command!='y' && command!='n' && command!='e' && command!='b' && command!='Y' && command!='N' && command!='E' && command!='B' && command!='D' && command!='d'){
        printf("\t>> To Edit press 'y' \n");
        printf("\t>> To delete record 'd' \n");
        printf("\t>> To View New record 'n' \n");
        printf("\t>> to back press 'b' \n");
        printf("\t>> To Main menu 'e'  \n");
        scanf(" %c",&command);
    }
    if(command=='y'|| command=='Y'){
        edit_student();
    }
    else if(command=='n' || command=='N'){
        search_student();
    }
    else if(command=='b' || command=='B'){
        view_student();
    }
    else if(command=='D' || command=='d'){
        delete_student();
    }
    else{
        main();
    }
}

void edit_student(){
    system("cls");
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t  EDIT STUDENT DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    struct student stu;
    struct course cou;
    FILE *student_record;
    FILE *temp;
    FILE *course_record;
    char input_id[15];
    int found;
    float gpa=0,gpv=0,credit=0;
    char command;

    printf("\t\t\t Enter University ID :- ");
    scanf(" %[^\n]s",input_id);
    student_record=fopen("Student record.txt","r");
    temp=fopen("temp1.txt","w");
    while(fread(&stu,sizeof(struct student),1,student_record)){
        if(strcmp(input_id,stu.s_id)==0){
            found=1;
            printf("\n\t\t\t Enter your Name to update       :- ");
            scanf(" %[^\n]s",stu.name);
            printf("\n\t\t\t Enter your department to update :- ");
            scanf(" %[^\n]s",stu.department);
            printf("\n\n\t\t\t How many courses you followed/following? ");
            scanf("%d",&stu.no_of_courses);

            for(int i=0;i<stu.no_of_courses;i++){
                printf("\n\t\t\t\t Enter %d course    :- ",i+1);
                scanf(" %[^\n]s",stu.many[i].sc_name);
                printf("\n\t\t\t\t Enter your grade  :- ");
                scanf(" %c",&stu.many[i].grade);
            }
            for(int i=0;i<stu.no_of_courses;i++){
                course_record = fopen("Course record.txt","r");
                while(fread(&cou,sizeof(struct course),1,course_record)){
                    if(strcmp(stu.many[i].sc_name,cou.course_name)==0){
                        credit+=cou.credit_value;
                        if(stu.many[i].grade=='A'){
                            gpv=cou.credit_value*4.0;
                        }
                        else if(stu.many[i].grade=='B'){
                            gpv=cou.credit_value*3.0;
                        }
                        else if(stu.many[i].grade=='C'){
                            gpv=cou.credit_value*2.5;
                        }
                        else if(stu.many[i].grade=='D'){
                            gpv=cou.credit_value*1.5;
                        }
                        else{
                            gpv=0;
                        }
                        break;
                    }
                }
                gpa+=gpv;
                fclose(course_record);
            }
            stu.gpa=gpa/credit;
        }
        fwrite(&stu,sizeof(struct student),1,temp);
    }
    fclose(student_record);
    fclose(temp);

    if(found){
        student_record=fopen("Student record.txt","w");
        temp=fopen("temp1.txt","r");

        while(fread(&stu,sizeof(struct student),1,temp)){
            fwrite(&stu,sizeof(struct student),1,student_record);
        }
        printf("\n\t\tRecord saved succesfully\n");
        fclose(student_record);
        fclose(temp);
    }
    else{
        printf("\n\t\t\t The record is not found \n\n");
    }
    printf("\n\t>> To Edit press 'y' \n");
    printf("\t>> View new record press 'n' \n");
    printf("\t>> To main menu 'e' \n");
    scanf(" %c",&command);

    while(command!='n' && command!='e' && command!='y' && command!='N' && command!='E' && command!='Y'){
        printf("\n\t>> To Edit press 'y' \n");
        printf("\n\t>> View new record press 'n' \n");
        printf("\t>> to Exit press 'e' \n");
        scanf(" %c",&command);
    }
    if(command=='n' || command=='N'){
        view_student();
    }
    else if(command=='y' || command=='Y'){
        edit_student();
    }
    else{
        main();
    }
}

void delete_student(){
    system("cls");
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t DELETE STUDENT DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    struct student stu;
    struct course cou;
    FILE *student_record;
    FILE *temp;
    FILE *course_record;
    char input_id[15];
    int found;
    float gpa=0,gpv=0,credit=0;
    char command;

    printf("\t\t\t Enter University ID :- ");
    scanf(" %[^\n]s",input_id);
    student_record=fopen("Student record.txt","r");
    temp=fopen("temp2.txt","w");
    while(fread(&stu,sizeof(struct student),1,student_record)){
        if(strcmp(input_id,stu.s_id)==0){
            found=1;
        }
        else{
            fwrite(&stu,sizeof(struct student),1,temp);
        }
    }
    fclose(student_record);
    fclose(temp);

    if(found){
        student_record=fopen("Student record.txt","w");
        temp=fopen("temp2.txt","r");

        while(fread(&stu,sizeof(struct student),1,temp)){
            fwrite(&stu,sizeof(struct student),1,student_record);
        }
        printf("\n\t\tRecord deleted succesfully\n");
        fclose(student_record);
        fclose(temp);
    }
    else{
        printf("\n\t\t\t The record is not found \n\n");
    }
    printf("\n\t>> To Edit press 'y' \n");
    printf("\t>> View new record press 'n' \n");
    printf("\t>> To main menu 'e' \n");
    scanf(" %c",&command);

    while(command!='n' && command!='e' && command!='y' && command!='N' && command!='E' && command!='Y'){
        printf("\n\t>> To Edit press 'y' \n");
        printf("\n\t>> View new record press 'n' \n");
        printf("\t>> to Exit press 'e' \n");
        scanf(" %c",&command);
    }
    if(command=='n' || command=='N'){
        view_student();
    }
    else if(command=='y' || command=='Y'){
        edit_student();
    }
    else{
        main();
    }
}

void add_course(){

    system("cls");
    FILE *course_record;
    char command;
    struct course cou;
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   ADD COURSE DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\n\t\t\t Enter Course ID    :- ");
    scanf(" %[^\n]s",cou.course_id);
    printf("\n\t\t\t Enter Course name  :- ");
    scanf(" %[^\n]s",cou.course_name);
    printf("\n\t\t\t Enter Credit value :- ");
    scanf("%f",&cou.credit_value);

    course_record = fopen("Course record.txt","a");
    fwrite(&cou,sizeof(struct course),1,course_record);
    fclose(course_record);

    printf("\n\t\t Details succesfully saved!!!\n\n");

    printf("\t>> Add new record press 'y' \n");
    printf("\t>> To main menu press 'e'   \n");
    scanf(" %c",&command);

    while(command!='y' && command!='e' && command!='Y' && command!='E'){
        printf("\t>> Add new record press 'y' \n");
        printf("\t>> To main menu press 'e'   \n");
        scanf(" %c",&command);
    }
    if(command=='y' || command=='Y'){
        add_course();
    }
    else{
        main();
    }
}

void view_course(){
    system("cls");

    char command;
    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   VIEW COURSE DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\n\n\t\t\t\t 1.All Courses (Press 1)\n");
    printf("\t\t\t\t 2.Search course and edit (Press 2)\n\n\n");
    printf("\t\t>>To main menu press 'e' \n");
    scanf(" %c",&command);

    while(command!='1' && command!='2' && command!='e'){
        printf("\n\n\t\t\t\t 1.All Courses (Press 1)\n");
        printf("\t\t\t\t 2.Search course and edit (Press 2)\n\n\n");
        printf("\t>>To main menu press 'e'  \n");
        scanf(" %c",&command);
    }
    if(command=='1'){
        view_all_courses();
    }
    else if(command=='2'){
        search_course();
    }
    else{
        main();
    }
}

void view_all_courses(){
    system("cls");
    FILE *course_record;
    char course_id[10];
    struct course cou;
    char command;

    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   VIEW COURSE DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    course_record=fopen("Course record.txt","r");
    if(course_record==NULL){
        printf("\n\t\tNo records available. please enter records.\n\n");
    }
    else{
        while(fread(&cou,sizeof(struct course),1,course_record)){

            printf("\t\t\t Course ID :- %s\n\n",cou.course_id);
            printf("\t\t\t Course name :- %s\n\n",cou.course_name);
            printf("\t\t\t Credit value :- %.1f\n\n\n\n",cou.credit_value);
        }
    }
    fclose(course_record);
    printf("\t>> To Edit record press 'n' \n");
    printf("\t>> To delete record press 'd' \n");
    printf("\t>> Go to back press 'b' \n");
    printf("\t>> To main menu press 'e' \n");
    scanf(" %c",&command);

    while(command!='b' && command!='e' && command!='B' && command!='E' && command!='D' && command!='d' && command!='N' && command!='n'){
        printf("\t>> To Edit record press 'n' \n");
        printf("\t>> To delete record press 'd' \n");
        printf("\t>> Go to back press 'b' \n");
        printf("\t>> To main menu press 'e' \n");
        scanf(" %c",&command);
    }
    if(command=='b' || command=='B'){
        view_course();
    }
    else if(command=='N' || command=='n'){
        edit_course();
    }
    else if(command=='D' || command=='d'){
        delete_course();
    }
    else{
        main();
    }
}

void search_course(){
    system("cls");
    FILE *course_record;
    char course_id[10];
    struct course cou;
    char command;
    char input_id[10];
    int found;

    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   VIEW COURSE DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\t\t\t\t Enter course ID :- ");
    scanf(" %[^\n]s",input_id);

    course_record=fopen("Course record.txt","r");
    if(course_record==NULL){
        printf("\n\t\tNo records available. please enter records.\n\n");
    }
    else{
        while(fread(&cou,sizeof(struct course),1,course_record)){
            if(strcmp(input_id,cou.course_id)==0){
                found=1;
                printf("\n\t\t\t\t Course name  :- %s\n\n",cou.course_name);
                printf("\t\t\t\t Credit value :- %.2f\n\n\n\n",cou.credit_value);
            }
        }

        fclose(course_record);

        if(!found){
            printf("\n\t\t\t The record is not found\n\n");
        }
    }
    printf("\t>> Search new record press 'n' \n");
    printf("\t>> To Edit record press 's' \n");
    printf("\t>> To delete record press 'd' \n");
    printf("\t>> to back press 'b' \n");
    printf("\t>> To main menu 'e' \n");
    scanf(" %c",&command);

    while(command!='n' && command!='s' && command!='b' && command!='e' && command!='N' && command!='S' && command!='B' && command!='E' && command!='D' && command!='d'){
        printf("\t>> Search new record press 'n' \n");
        printf("\t>> To Edit record press 's' \n");
        printf("\t>> To delete record press 'd' \n");
        printf("\t>> to back press 'b' \n");
        printf("\t>> To main menu 'e' \n");
        scanf(" %c",&command);
    }
    if(command=='n' || command=='N'){
        search_course();
    }
    else if(command=='s' || command=='S'){
        edit_course();
    }
    else if(command=='b' || command=='B'){
        view_course();
    }
    else if(command=='D' || command=='d'){
        delete_course();
    }
    else{
        main();
    }
}

void edit_course(){
    system("cls");
    FILE *course_record;
    FILE *temp;
    char course_id[10];
    struct course cou;
    char command;
    char input_id[10];
    int found;

    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t   EDIT COURSE DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\t\t\t\t Enter course to update ID :- ");
    scanf(" %[^\n]s",input_id);

    temp=fopen("temp.txt","w");
    course_record=fopen("Course record.txt","r");
    while(fread(&cou,sizeof(struct course),1,course_record)){
        if(strcmp(input_id,cou.course_id)==0){
            found=1;
            printf("\n\t\t\t\t Enter New Course name :-");
            scanf(" %[^\n]s",cou.course_name);
            printf("\n\t\t\t\t Enter Credit value :- ");
            scanf("%f",&cou.credit_value);
        }
        fwrite(&cou,sizeof(struct course),1,temp);
    }
    fclose(course_record);
    fclose(temp);

    if(found){
        course_record=fopen("Course record.txt","w");
        temp=fopen("temp.txt","r");

        while(fread(&cou,sizeof(struct course),1,temp)){
            fwrite(&cou,sizeof(struct course),1,course_record);
        }
        printf("\n\t\tRecord saved succesfully.\n");
        fclose(course_record);
        fclose(temp);
    }else{
        printf("\n\t\t\t The record is not found\n\n");
    }
    printf("\n\n\t>> Search new record press 'n' \n");
    printf("\t>> to back press 'b' \n");
    printf("\t>> To main menu 'e' \n");
    scanf(" %c",&command);

    while(command!='n' && command!='b' && command!='e' && command!='N' && command!='B' && command!='E'){
        printf("\n\n\t>> Search new record press 'n' \n");
        printf("\t>> to back press 'b' \n");
        printf("\t>> To main menu 'e' \n");
        scanf(" %c",&command);
    }
    if(command=='n' || command=='N'){
        search_course();
    }
    else if(command=='b' || command=='B'){
        view_course();
    }
    else{
        main();
    }
}

void delete_course(){
    system("cls");
    FILE *course_record;
    FILE *temp;
    char course_id[10];
    struct course cou;
    char command;
    char input_id[10];
    int found;

    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t  DELETE COURSE DETAILS\n");
    printf("\t\t\t\t\t -----------------------\n\n");

    printf("\t\t\t\t Enter course to update ID :- ");
    scanf(" %[^\n]s",input_id);

    temp=fopen("temp3.txt","w");
    course_record=fopen("Course record.txt","r");
    while(fread(&cou,sizeof(struct course),1,course_record)){
        if(strcmp(input_id,cou.course_id)==0){
            found=1;
        }
        else{
            fwrite(&cou,sizeof(struct course),1,temp);
        }
    }
    fclose(course_record);
    fclose(temp);

    if(found){
        course_record=fopen("Course record.txt","w");
        temp=fopen("temp3.txt","r");

        while(fread(&cou,sizeof(struct course),1,temp)){
            fwrite(&cou,sizeof(struct course),1,course_record);
        }
        printf("\n\t\tRecord Deleted succesfully.\n");
        fclose(course_record);
        fclose(temp);
    }else{
        printf("\n\t\t\t The record is not found\n\n");
    }
    printf("\n\n\t>> Search new record press 'n' \n");
    printf("\t>> to back press 'b' \n");
    printf("\t>> To main menu 'e' \n");
    scanf(" %c",&command);

    while(command!='n' && command!='b' && command!='e' && command!='N' && command!='B' && command!='E'){
        printf("\n\n\t>> Search new record press 'n' \n");
        printf("\t>> to back press 'b' \n");
        printf("\t>> To main menu 'e' \n");
        scanf(" %c",&command);
    }
    if(command=='n' || command=='N'){
        search_course();
    }
    else if(command=='b' || command=='B'){
        view_course();
    }
    else{
        main();
    }
}

int main(){
    system("cls");
    char main_input;

    printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t\t  HOME\n");
    printf("\t\t--------------------------------------------------------------------------\n\n");

    printf("\t\t\t\t\t1- Add students details (press 1)\n");
    printf("\t\t\t\t\t2- View student details (press 2)\n");
    printf("\t\t\t\t\t3- Add course details (press 3)\n");
    printf("\t\t\t\t\t4- View course details (press 4)\n\n");

    printf("\t\t\t\t\t To exit press E\n\n");
    scanf("%c",&main_input);

    while(main_input!='1' && main_input!='2' && main_input!='3' && main_input!='4' && main_input!='E'){
        printf("Wrong input, please enter (1,2,3,4,E)\n");
        scanf("%c",&main_input);
    }
    if(main_input=='1'){
        add_student();
    }
    if(main_input=='2'){
        view_student();
    }
    if(main_input=='3'){
        add_course();
    }
    if(main_input=='4'){
        view_course();
    }
    else{
        exit(1);
    }
    return 0;
}
