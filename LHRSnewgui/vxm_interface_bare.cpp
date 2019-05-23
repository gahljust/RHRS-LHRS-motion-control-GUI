#include <iostream>
#include <fstream>
#include <stdio.h>   					// Standard input/output definitions
#include <unistd.h>  					// UNIX standard function definitions
#include <fcntl.h>   					// File control definitions
#include <errno.h>   					// Error number definitions
#include <termios.h> 					// POSIX terminal control definitions
#include <cmath>					   // Math functions
#include <ctime>
using namespace std;

// HORIZONTAL MOTOR IS MOTOR 1
// VERTICAL MOTOR IS MOTOR 2
// ROTATING MOTOR IS MOTOR 3
// MOTOR CONTROLLER IS PLUGGED INTO RS-232 PORT "ttyS0"

// CONVERTS A STRING OF INTEGERS INTO AN INTEGER.
// THE FUNCTION CAN ACCEPT NEGATIVE NUMBERS.
// EXAMPLES:  abcdefg
int string_to_int(string input)
{
    int size, foo = 0;
    bool negative = false;		                                 // is the value negative
    double result = 0;		                                     // double to store result
    string magnitude = input;	                                 // string will hold all the numbers for analysis
    for(unsigned int i = 0; i < magnitude.length(); i++)
        if(magnitude[i] > 47 && magnitude[i] < 58)                // if this char is a number
        {
            if(i > 0 && magnitude[i-1] == '-')	                 // if negative sign precedes number
                negative = true;                                 // then this is a negative number
            magnitude = magnitude.substr(i);                     // the magnitude is the rest of the string
            break;                                               // exit loop, we found the number
        }
    size = magnitude.length();	                                // don't loop past the end of string
    for(int i = 0; i < size; i++)                               // loop through string backwards
    {
        if(magnitude[size-1-i] > 47 && magnitude[size-1-i] < 58)                          // if there is another number
            result += (magnitude[size-1-i]-48)*pow(10.0,static_cast<double>(i-foo));      // add it
        else    foo++;		                                                              // must subtract foo from i to get order of magnitude correct
                                                                                          // in the conversion to integer. foo = 0 if n     o letters in string.
                                                                                          // this simply allows "hello, i am 25 years old" to return 25.
    }
    if(negative)
        result = -1 * result;
    return static_cast<int>(result);
}

class Log
{
  private:
    bool isOpen;                    // Set to true when file is successfully opened
    char outLogName[256];           // name of log file
    fstream outLog;                 // file stream object used for writing to log file
    ifstream inLog;                 // file stream object used for reading from log file
    string intToString(int i)       // only for positive integers
    {
        string s1 = "";
        while(i / 10 > 0)
        {
            s1 += static_cast<char>((i % 10) + 30);
            i = i / 10;
        }
        return s1;
    }

  public:
    Log()
    {

        sprintf(outLogName, "vxm_log.txt");
        outLog.open(outLogName, ios::out | ios::app);    // open in output and append mode
        inLog.open(outLogName);                          // open in readonly mode
        if(outLog.is_open() && inLog.is_open())
        {

            isOpen = true;
        }
        else
        {

            isOpen = false;
        }
    }
    ~Log()                     // object destructor: closes log file streams
    {
        outLog.close();
                inLog.close();
    }
    void writeSentCommandToLog(string s1)
    {
        if(isOpen)
        {
            if(s1.compare("") == 0) outLog <<  endl;                              // if empty string, write line feed
            else outLog << "&& Command issued to motors: " << s1 << endl;         // write command sent with && tag for reading
        }
    }
    void comment(){
        if(isOpen) outLog << "//";
    }
    void writeTime()
    {
        if(isOpen)
        {
            time_t t = time(0);                          // get time now
            struct tm * now = localtime( & t );
            char temp[128];
            sprintf(temp, "** %i/%i/%i @ %i:%i",now->tm_mon+1,now->tm_mday,now->tm_year+1900,now->tm_hour,now->tm_min);
            outLog << temp << endl;
        }
    }

    void writeMotorMove(string motor, string distance)
    {
        if(isOpen)
        {
            if(motor.compare("h")==0) motor = "horizontal";
            if(motor.compare("v")==0) motor = "vertical";
            if(motor.compare("t")==0) motor = "theta";
            outLog << "## " << motor << " motor movement command of " << distance << " steps stored." << endl;
        }
    }
    void writeFinalMotorPosition()
    {
        if(isOpen)
        {
            int x = 0;               // x keeps track of horizontal distance
            x = getInitialX();       // gets previous 'final' distance from log using ++ tag
            x += getDeltaX();        // gets total displacement of horizontal motor
            int y = 0;               // y analagous to x for vertical motor using -- tag in log file
            y = getInitialY();
            y += getDeltaY();
            int t = 0;
            t = getInitialT();
            t += getDeltaT();
            char temp[64];
            sprintf(temp, "++ Final horizontal position: %i", x);	   // use ++ tags for horizontal motor
            outLog << temp << endl;					                   // write final horizontal position to log
            sprintf(temp, "-- Final vertical position: %i", y);	       // use -- for final vertical position
            outLog << temp << endl;					                   // write final vertical position to log
            sprintf(temp, "<< Final theta position: %i", t);	       // use << for final theta position
            outLog << temp << endl;					                   // write final theta position to log
        }
    }
    // RETURNS THE POSITION OF THE HORIZONTAL MOTOR AT THE BEGINNING OF
    // THE CURRENT SESSION
    int getInitialX()
    {
        string temp, temp2;
        if(isOpen)
        {
            int startLine = getLast("++");                     // find line which contains initial x info in log file
            inLog.seekg(0);                                    // go to the beginning of the file
            for(int i = 0; i < startLine; i++)                 // use getline() to navigate to correct line in log file
                if(!inLog.eof()) getline(inLog, temp);
            inLog.clear();                                     // clear eof() bit
                        temp2 = temp.substr(0,30);
            if(temp2.compare("++ Final horizontal position: ")==0)           // if this is final horizontal movement line
                temp = temp.substr(30);                                      // obtain the integer from the string
            else temp = "0";                                                // else reset temp to 0
        }
        return string_to_int(temp);                                         // return integer form of last position
    }
    // ANALAGOUS TO getInitialX() FOR VERTICAL MOTOR
    int getInitialY()
    {
        string temp, temp2;
        if(isOpen)
        {
            int startLine = getLast("--");
            inLog.seekg(0);
            for(int i = 0; i < startLine; i++)
                getline(inLog, temp);
            inLog.clear();
                        temp2 = temp.substr(0,28);
            if(temp2.compare("-- Final vertical position: ")==0)
                temp = temp.substr(28);
            else temp = "0";
        }
        return string_to_int(temp);
    }
        // ANALAGOUS TO getInitialX() FOR THETA MOTOR
    int getInitialT(){
        string temp, temp2;
        if(isOpen){
            int startLine = getLast("<<");
            inLog.seekg(0);
            for(int i = 0; i < startLine; i++)
                getline(inLog, temp);
            inLog.clear();
            temp2 = temp.substr(0,25);
            if(temp2.compare("<< Final theta position: ")==0)
                temp = temp.substr(25);
            else temp = "0";
        }
        return string_to_int(temp);
    }
    // RETURNS THE TOTAL MOVEMENT OF THE HORIZONTAL MOTOR SINCE THE BEGINNING
    // OF THIS SESSION
    int getDeltaX()
    {
        string moves, temp;
        int result = 0, nextPos;		                     // initialize to zero
        moves = getCurrentMoves();		                    // get all moves of motors in current session
        if(moves.length() == 0) return 0;	                // if no moves, return 0
        while(moves.length() > 0)		                    // while still more moves to consider
        {
            nextPos = moves.find(": ");		                // find beginning of next move (before ": "
            moves = moves.substr(nextPos+2);                // delete previous command from list of commands
            nextPos = moves.find(",");                      // find end of next move
            temp = moves.substr(0,nextPos);                 // extract next move from string
            if(temp.substr(0,2).compare("I1")==0)           // if this is a HORIZONTAL motor movement
            {
                temp = temp.substr(3);			            // remove I#M from command
                result = result + string_to_int(temp);      // add magnitude to result
            }
            moves = moves.substr(nextPos+1);	            // deletes command and comma just considered
        }
        return result;		                                // return magnitude of displacement of horizontal motor
    }
    // ANALAGOUS TO getDeltaX() FOR VERTICAL MOTOR
    int getDeltaY()
    {
        string moves, temp;
        int result = 0;
        moves = getCurrentMoves();
        if(moves.length() == 0) return 0;
        while(moves.length() > 0)
        {
            int nextPos = moves.find(": ");
            moves = moves.substr(nextPos+2);
            nextPos = moves.find(",");
            temp = moves.substr(0,nextPos);
            if(temp.substr(0,2).compare("I2")==0)
            {
                temp = temp.substr(3);
                result = result + string_to_int(temp);
            }
            moves = moves.substr(nextPos+1);
        }
        return result;
    }
    // ANALAGOUS TO getDeltaX() FOR THETA MOTOR
    int getDeltaT(){
        string moves, temp;
        int result = 0;
        moves = getCurrentMoves();
        if(moves.length() == 0) return 0;
        while(moves.length() > 0){
            int nextPos = moves.find(": ");
            moves = moves.substr(nextPos+2);
            nextPos = moves.find(",");
            temp = moves.substr(0,nextPos);
            if(temp.substr(0,2).compare("I3")==0){
                temp = temp.substr(3);
                result = result + string_to_int(temp);
            }
            moves = moves.substr(nextPos+1);
        }
        return result;
    }
    // RETURNS THE LINE NUMBER OF THE LAST KEY (RETURNS 0 IF NOT FOUND)
    int getLast(const char* key)
    {
        int lastPos = 0;                                 // keeps track of last line in which 'key' appears in log file
        if(isOpen)
        {
            string temp;                                 // used to store current line in log file
            int count = 0;                               // count is int used to store line index
            inLog.seekg(0);                              // start at beginning of log file
            while(!inLog.eof())                          // go to the end of the log file
            {
                count++;                                 // the first line is line 10
                getline(inLog, temp);                    // get the next line
                if(temp.substr(0,2).compare(key) == 0)   // if the first two characters of this line match the key
                    lastPos = count;                     // record which line it is
            }
            inLog.clear();                                // clear the eof bit from the filestream
        }
        return lastPos;                                   // returns the LAST line on which key is found
    }
    // RETURNS A STRING OF ALL THE MOVE COMMANDS ENTERED THIS INSTANCE OF PROGRAM
    string getCurrentMoves()
    {
        string result = "";
        if(isOpen)
        {
            int count = 0;
            int start = getLast("**");                                          // find out which line is the first of this instance
            string temp = "";
            inLog.seekg(0);                                                     // start at beginning of file
            while(!inLog.eof())                                                 // don't go past the end of the file
            {
                count++;                                                        // keep track of lines
                getline(inLog, temp);                                           // get the current line
                                                                                // if we are viewing the current instance AND we are viewing a motor move
                if(count >= start && temp.substr(0,2).compare("&&") == 0)
                    result.append(temp);  // grab the line
            }
            inLog.clear();  // clear the eof bit
        }
        return result;  // return list of commands in one string
    }
};




class VXM_interface
{
    public:
    VXM_interface(){                                       // constructor will create new instances of VXM_interface objects
                                                          //		INITIALIZE ALL VALUES TO NULL		//
        port_open = false;	                              // boolian used to determine whether to read/write or not


        size = 0;		                                  // int for size of command to be sent



        command = "";                                      // string for command to be send



                vxmLog = new Log();                        // log object defined to log motor movements
                vxmLog->writeTime();	                   // write a time stamp to the log

        //		OPEN PORT AND PREPARE STEPPER MOTOR FOR USE		//
        open_port();			              // open port for read/write
        if(port_fd != -1)		             // if file opened successfully
            port_open = true;	             // set port_open (maybe need an else)
        write(port_fd, "G", 1);		         // put motor controller into immediate command mode
                usleep(1);			         // sleep for a microsecond to give vxm time
        write(port_fd, "setM1M4,", 8);	      // initialize motor 1 to be horizontal motor  M(motor axis) M(motor type)
                usleep(1);                    // note motor type is important A_T's have a different motor type than the mains which themselves have two different motor types
        write(port_fd, "setM2M5,", 8);	      // initialize motor 2 to be vertical motor
                usleep(1);
        write(port_fd, "C", 1);		          // clear RAM
                usleep(1);
       // write(port_fd,"S3M16,",8);



    }
    ~VXM_interface(){                              // destructor closes the RS-232 port when object dies
        close(port_fd);


    }


    bool get_port_open()  {
        return port_open;
    }


    int get_port_fd(){
        return port_fd;
    }


    int get_size(){
        return size;
    }


    string get_command(){
        return command;
    }


    void set_port_open(bool input){
        port_open = input;
    }

    void set_size(int input){
        size = input;
    }


   void set_motor_3(){
        write(port_fd, "setDM65,", 8);
                usleep(1);
        write(port_fd, "setM3M4,", 8);
                usleep(1);
        write(port_fd,"S3M16,R",16);

    }


    // set the current command
    void set_command(string input){
        command = input;
        size = input.length();
    }

    // verifies that the vxm is awaiting commands
    int confirm_connection(){
        int ret = 0;
        while(ret != -1)  ret = read(port_fd, buf, 255);
        write(port_fd, "V", 1);
        ret = read(port_fd, buf, 255);
        if(ret != -1)
            if(buf[0] == 'R') return 1;
        return 0;
    }

                                                                               // enter a new CUSTOM move command
        void new_move_command(string motor, string distance){
                                                                               // BUILD COMMAND
        size = distance.length() + 4;	                                       // need to add "I#M" and ","
        if(motor.compare("horizontal") == 0 || motor.compare("h") == 0)
            command = "I1M" + distance + ",";
        else if(motor.compare("vertical") == 0 || motor.compare("v") == 0)
            command = "I2M" + distance + ",";
        else if(motor.compare("theta")==0 || motor.compare("t")==0)
            command = "S3M16, I3M" + distance + ",";                              // added S3 command, and changed size to the length of command to change speed properly
            size = command.length();
                                                                                  // CONFIRM NEW COMMAND

            vxmLog->writeMotorMove(motor, distance);                               // write new move command to log
    }



    void open_port()
    {
        port_fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NONBLOCK);		       // open port
        if (port_fd == -1)
            perror("open_port: Unable to open /dev/ttyUSB1");                     // couldn't open port
        else
            fcntl(port_fd, F_SETFL, 0);									           // ?? reset all file descriptor flags ??

    }



    void send_command()
    {
        //		VERIFY COMMAND WITH USER		//
        unsigned char to_send[size];

        //// CONVERT AND WRITE THE COMMAND TO PORT
        // TRANSFER INPUT TO UNSIGNED CHAR VARIABLE
        for(int k = 0; k < size; k++)
            to_send[k] = command[k];
        write(port_fd, "C,", 2);
        usleep(1);
        write(port_fd, to_send, size);
        usleep(1);
        write(port_fd, "R", 1);

                vxmLog->writeSentCommandToLog(command);
                vxmLog->writeFinalMotorPosition(); //new
    }


    void exit_interface()
    {
                                                                        // QUIT COMMAND MODE AND CLOSE PORT
        write(port_fd, "C,", 2);										// clear RAM
        usleep(1);
        write(port_fd, "Q", 1);											// enter jogging mode
        close(port_fd);												// close file (/dev/ttyS0)

                                                                      // WRITE THE FINAL MOTOR POSITIONS IN THE LOG FILE

                                                                      // WRITE A BLANK LINE TO LOG FILE FOR SEPERATION OF DATA
        vxmLog->writeSentCommandToLog("");

    }

    string read_port()
    {
        int ret = read(port_fd,buf,255);
        string output;
        for (int i = 0;i<(sizeof(buf))/sizeof(buf[0]);i++)
        {
                output += string(1,buf[i]);
        }



        write(port_fd,"C",1);

        return output;
    }

    private:


        bool port_open;		// port is open?  (true/false)
        int port_fd;		    // file descriptor for port (/dev/ttyS0 [RS-232 port])

        int size;		        // size of current command in bytes (chars)
        string command;		// current command, ready to be sent to stepper motor

        Log *vxmLog;		// log file object, used for keeping log file
        char buf[256];		// buffer for reading from VXM
};



class Log2
{
private:
    bool isOpen2;                    // Set to true when file is successfully opened
    char outlog2Name[256];           // name of log2 file
    fstream outlog2;                 // file stream object used for writing to log2 file
    ifstream inlog2;                 // file stream object used for reading from log2 file
    string intToString(int i)       // only for positive integers
    {
        string s2 = "";
        while(i / 10 > 0)
        {
            s2 += static_cast<char>((i % 10) + 30);
            i = i / 10;
        }
        return s2;
    }

public:
    Log2()
    {

        sprintf(outlog2Name, "vxm_log2.txt");
        outlog2.open(outlog2Name, ios::out | ios::app);    // open in output and append mode
        inlog2.open(outlog2Name);                          // open in readonly mode
        if(outlog2.is_open() && inlog2.is_open())
        {

            isOpen2 = true;
        }
        else
        {

            isOpen2 = false;
        }
    }
    ~Log2()                     // object destructor: closes log2 file streams
    {
        outlog2.close();
        inlog2.close();
    }
    void writeSentCommandTolog2(string s2)
    {
        if(isOpen2)
        {
            if(s2.compare("") == 0) outlog2 <<  endl;                              // if empty string, write line feed
            else outlog2 << "&& Command issued to motors: " << s2 << endl;         // write command sent with && tag for reading
        }
    }
    void comment(){
        if(isOpen2) outlog2 << "//";
    }
    void writeTime()
    {
        if(isOpen2)
        {
            time_t t = time(0);                          // get time now
            struct tm * now = localtime( & t );
            char temp[128];
            sprintf(temp, "** %i/%i/%i @ %i:%i",now->tm_mon+1,now->tm_mday,now->tm_year+1900,now->tm_hour,now->tm_min);
            outlog2 << temp << endl;
        }
    }

    void writeMotorMove(string motor2, string distance2)
    {
        if(isOpen2)
        {
            if(motor2.compare("x1")==0) motor2 = "horizontalx1";
            if(motor2.compare("y1")==0) motor2 = "verticaly1";
            if(motor2.compare("x2")==0) motor2 = "horizantalx2";
            if(motor2.compare("y2")==0) motor2 = "horizantaly2";
            outlog2 << "## " << motor2 << " motor movement command of " << distance2 << " steps stored." << endl;
        }
    }
    void writeFinalMotorPosition()
    {
        if(isOpen2)
        {
            int x1 = 0;               // x keeps track of horizontal distance
            x1 = getInitialX1();       // gets previous 'final' distance from log2 using ++ tag
            x1 += getDeltaX1();        // gets total displacement of horizontal motor
            int y1 = 0;               // y analagous to x for vertical motor using -- tag in log2 file
            y1 = getInitialY1();

            y1 += getDeltaY1();

            int x2 = 0;

            x2 = getInitialX2();

            x2 += getDeltaX2();

            int y2 = 0;

            y2 = getInitialY2();

            y2 = getDeltaY2();

            char temp[64];
            sprintf(temp, "++ Final horizontalx1 position: %i", x1);       // use ++ tags for horizontal motor
            outlog2 << temp << endl;                                       // write final horizontal position to log2
            sprintf(temp, "-- Final verticaly1 position: %i", y1);           // use -- for final vertical y1 position
            outlog2 << temp << endl;

            sprintf(temp, "<< Final horizontalx2 position: %i", x2);
            outlog2 << temp << endl; // final hor. x2 position

            sprintf(temp, ">> Final horizontaly2 position: %i", y2);
            outlog2 << temp << endl;                                       // write final ver. y2 position
        }
    }
    // RETURNS THE POSITION OF THE HORIZONTAL MOTOR AT THE BEGINNING OF
    // THE CURRENT SESSION
    int getInitialX1()
    {
        string temp, temp2;
        if(isOpen2)
        {
            int startLine = getLast("++");                     // find line which contains initial x info in log2 file
            inlog2.seekg(0);                                    // go to the beginning of the file
            for(int i = 0; i < startLine; i++)                 // use getline() to navigate to correct line in log2 file
                if(!inlog2.eof()) getline(inlog2, temp);
            inlog2.clear();                                     // clear eof() bit
            temp2 = temp.substr(0,30);
            if(temp2.compare("++ Final horizontalx1 position: ")==0)           // if this is final horizontal movement line
                temp = temp.substr(30);                                      // obtain the integer from the string
            else temp = "0";                                                // else reset temp to 0
        }
        return string_to_int(temp);                                         // return integer form of last position
    }
    // ANALAGOUS TO getInitialX() FOR VERTICAL MOTOR
    int getInitialY1()
    {
        string temp, temp2;
        if(isOpen2)
        {
            int startLine = getLast("--");
            inlog2.seekg(0);
            for(int i = 0; i < startLine; i++)
                getline(inlog2, temp);
            inlog2.clear();
            temp2 = temp.substr(0,28);
            if(temp2.compare("-- Final verticaly1 position: ")==0)
                temp = temp.substr(28);
            else temp = "0";
        }
        return string_to_int(temp);
    }
    // ANALAGOUS TO getInitialX() FOR x2 MOTOR
    int getInitialX2(){
        string temp, temp2;
        if(isOpen2){
            int startLine = getLast("<<");
            inlog2.seekg(0);
            for(int i = 0; i < startLine; i++)
                getline(inlog2, temp);
            inlog2.clear();
            temp2 = temp.substr(0,25);
            if(temp2.compare("<< Final horizontalx2 position: ")==0)
                temp = temp.substr(25);
            else temp = "0";
        }
        return string_to_int(temp);
    }

    int getInitialY2(){
        string temp, temp2;
        if(isOpen2){
            int startLine = getLast(">>");
            inlog2.seekg(0);
            for(int i = 0; i < startLine; i++)
                getline(inlog2, temp);
            inlog2.clear();
            temp2 = temp.substr(0,25);
            if(temp2.compare(">> Final horizontaly2 position: ")==0)
                temp = temp.substr(25);
            else temp = "0";
        }
        return string_to_int(temp);
    }
    // RETURNS THE TOTAL MOVEMENT OF THE HORIZONTAL MOTOR SINCE THE BEGINNING
    // OF THIS SESSION
    int getDeltaX1()
    {
        string moves, temp;
        int result = 0, nextPos;                             // initialize to zero
        moves = getCurrentMoves2();                            // get all moves of motors in current session
        if(moves.length() == 0) return 0;                    // if no moves, return 0
        while(moves.length() > 0)                            // while still more moves to consider
        {
            nextPos = moves.find(": ");                        // find beginning of next move (before ": "
            moves = moves.substr(nextPos+2);                // delete previous command from list of commands
            nextPos = moves.find(",");                      // find end of next move
            temp = moves.substr(0,nextPos);                 // extract next move from string
            if(temp.substr(0,2).compare("I1")==0)           // if this is a HORIZONTAL motor movement
            {
                temp = temp.substr(3);                        // remove I#M from command
                result = result + string_to_int(temp);      // add magnitude to result
            }
            moves = moves.substr(nextPos+1);                // deletes command and comma just considered
        }
        return result;                                        // return magnitude of displacement of horizontal motor
    }
    // ANALAGOUS TO getDeltaX() FOR VERTICAL MOTOR
    int getDeltaY1()
    {
        string moves, temp;
        int result = 0;
        moves = getCurrentMoves2();
        if(moves.length() == 0) return 0;
        while(moves.length() > 0)
        {
            int nextPos = moves.find(": ");
            moves = moves.substr(nextPos+2);
            nextPos = moves.find(",");
            temp = moves.substr(0,nextPos);
            if(temp.substr(0,2).compare("I2")==0)
            {
                temp = temp.substr(3);
                result = result + string_to_int(temp);
            }
            moves = moves.substr(nextPos+1);
        }
        return result;
    }
    // ANALAGOUS TO getDeltaX2() FOR x2 MOTOR
    int getDeltaX2(){
        string moves, temp;
        int result = 0;
        moves = getCurrentMoves2();
        if(moves.length() == 0) return 0;
        while(moves.length() > 0){
            int nextPos = moves.find(": ");
            moves = moves.substr(nextPos+2);
            nextPos = moves.find(",");
            temp = moves.substr(0,nextPos);
            if(temp.substr(0,2).compare("I3")==0){
                temp = temp.substr(3);
                result = result + string_to_int(temp);
            }
            moves = moves.substr(nextPos+1);
        }
        return result;}

        int getDeltaY2(){
            string moves, temp;
            int result = 0;
            moves = getCurrentMoves2();
            if(moves.length() == 0) return 0;
            while(moves.length() > 0){
                int nextPos = moves.find(": ");
                moves = moves.substr(nextPos+2);
                nextPos = moves.find(",");
                temp = moves.substr(0,nextPos);
                if(temp.substr(0,2).compare("I4")==0){
                    temp = temp.substr(3);
                    result = result + string_to_int(temp);
                }
                moves = moves.substr(nextPos+1);
            }
            return result;
    }
    // RETURNS THE LINE NUMBER OF THE LAST KEY (RETURNS 0 IF NOT FOUND)
    int getLast(const char* key)
    {
        int lastPos = 0;                                 // keeps track of last line in which 'key' appears in log2 file
        if(isOpen2)
        {
            string temp;                                 // used to store current line in log2 file
            int count = 0;                               // count is int used to store line index
            inlog2.seekg(0);                              // start at beginning of log2 file
            while(!inlog2.eof())                          // go to the end of the log2 file
            {
                count++;                                 // the first line is line 10
                getline(inlog2, temp);                    // get the next line
                if(temp.substr(0,2).compare(key) == 0)   // if the first two characters of this line match the key
                    lastPos = count;                     // record which line it is
            }
            inlog2.clear();                                // clear the eof bit from the filestream
        }
        return lastPos;                                   // returns the LAST line on which key is found
    }
    // RETURNS A STRING OF ALL THE MOVE COMMANDS ENTERED THIS INSTANCE OF PROGRAM
    string getCurrentMoves2()
    {
        string result = "";
        if(isOpen2)
        {
            int count = 0;
            int start = getLast("**");                                          // find out which line is the first of this instance
            string temp = "";
            inlog2.seekg(0);                                                     // start at beginning of file
            while(!inlog2.eof())                                                 // don't go past the end of the file
            {
                count++;                                                        // keep track of lines
                getline(inlog2, temp);                                           // get the current line
                // if we are viewing the current instance AND we are viewing a motor move
                if(count >= start && temp.substr(0,2).compare("&&") == 0)
                    result.append(temp);  // grab the line
            }
            inlog2.clear();  // clear the eof bit
        }
        return result;  // return list of commands in one string
    }
};





class VXM_interface2
{
    public:
    VXM_interface2(){                                       // constructor will create new instances of VXM_interface objects
                                                          //		INITIALIZE ALL VALUES TO NULL		//
                                          // boolian used to determine whether to read/write or not

        port_open2 = false;

                                                  // int for size of command to be sent

        size2 = 0;

                                         // string for command to be send

        command2 = "";

        vxmLog2 = new Log2();                        // log object defined to log motor movements
        vxmLog2->writeTime();	                   // write a time stamp to the log


        //		OPEN PORT AND PREPARE STEPPER MOTOR FOR USE		//

        open_port2();			                  // open port for read/write
        if(port_fd2 != -1)		                  // if file opened successfully
            port_open2 = true;	                  // set port_open (maybe need an else)
        write(port_fd2, "G", 1);		          // put motor controller into immediate command mode
                usleep(1);			              // sleep for a microsecond to give vxm time
        write(port_fd2, "setM1M1,", 8);	          // initialize motor 1 to be horizontal A_T 1 motor  M(motor axis) M(motor type) see manual for types
                usleep(1);                        // note motor type is important A_T's have a different motor type than the mains which themselves have two different motor types
        write(port_fd2, "setM2M1,", 8);	          // initialize motor 2 to be vertical A_T 1 motor
                usleep(1);
        write(port_fd2, "setM3M1,", 8);	          // initialize motor 3 to be horizontal A_T 2 motor
                usleep(1);
        write(port_fd2, "setM4M1,", 8);	          // initialize motor 4 to be vertical A_T 2 motor
                usleep(1);
        write(port_fd2, "C", 1);		          // clear RAM
                usleep(1);



    }
    ~VXM_interface2(){                              // destructor closes the RS-232 port when object dies

        close(port_fd2);

    }


    bool get_port_open2()  {
        return port_open2;
    }


    int get_port_fd2(){
        return port_fd2;
    }


    int get_size2(){
        return size2;
    }


    string get_command2(){
        return command2;
    }


    void set_port_open2(bool input2){
        port_open2 = input2;
    }

    void set_size2(int input2){
        size2 = input2;
    }


   void set_command2(string input2){
        command2 = input2;
        size2 = input2.length();
    }

    int confirm_connection2(){
        int ret = 0;
        while(ret != -1)  ret = read(port_fd2, buf, 255);
        write(port_fd2, "V", 1);
        ret = read(port_fd2, buf, 255);
        if(ret != -1)
            if(buf[0] == 'R') return 1;
        return 0;
    }

                                                                               // enter a new CUSTOM move command

        void new_move_command2(string motor2, string distance2){
                                                                               // BUILD COMMAND
        size2 = distance2.length() + 4;	                                       // need to add "I#M" and ","
        if(motor2.compare("horizontal") == 0 || motor2.compare("x1") == 0)
            command2 = "I1M" + distance2 + ",";
        else if(motor2.compare("vertical") == 0 || motor2.compare("y1") == 0)
            command2 = "I2M" + distance2 + ",";
        else if(motor2.compare("horizontal") == 0 || motor2.compare("x2") == 0)
            command2 = "I3M" + distance2 + ",";
        else if(motor2.compare("vertical") == 0 || motor2.compare("y2") == 0)
            command2 = "I4M" + distance2 + ",";

                                                                                  // CONFIRM NEW COMMAND

            vxmLog2->writeMotorMove(motor2, distance2);                               // write new move command to log
    }


    void open_port2()
    {
    port_fd2 = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);		   // open port
    if (port_fd2 == -1)
        perror("open_port2: Unable to open /dev/ttyUSB0 ");                     // couldn't open port
    else
        fcntl(port_fd2, F_SETFL, 0);
    }


    void send_command2()
    {
        //		VERIFY COMMAND WITH USER		//
        unsigned char to_send2[size2];

        //// CONVERT AND WRITE THE COMMAND TO PORT
        // TRANSFER INPUT TO UNSIGNED CHAR VARIABLE
        for(int k = 0; k < size2; k++)
            to_send2[k] = command2[k];
        write(port_fd2, "C,", 2);
        usleep(1);
        write(port_fd2, to_send2, size2);
        usleep(1);
        write(port_fd2, "R", 1);


                vxmLog2->writeSentCommandTolog2(command2);
                vxmLog2->writeFinalMotorPosition(); //new
    }


    void exit_interface2()
    {
                                                                        // QUIT COMMAND MODE AND CLOSE PORT									// close file (/dev/ttyS0)

        write(port_fd2, "C,", 2);										// clear RAM
        usleep(1);
        write(port_fd2, "Q", 1);											// enter jogging mode
        close(port_fd2);

                                                                      // WRITE THE FINAL MOTOR POSITIONS IN THE LOG FILE

        vxmLog2->writeSentCommandTolog2("");
                                                                      // WRITE A BLANK LINE TO LOG FILE FOR SEPERATION OF DATA
    }


    private:

        bool port_open2;
        int port_fd2;       //file descriptor for /dev/ttyUSBxx
        int size2;
        string command2;
            // current command, ready to be sent to stepper motor

        char buf[256];		// buffer for reading from VXM

        Log2 *vxmLog2;
};
