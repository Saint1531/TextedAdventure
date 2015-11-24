#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum en_DIRS { NORTH, EAST, SOUTH, WEST };
enum en_ROOMS { SCIENCELAB, CLASSROOM202, START, HALLWAY1, CAFETERIA, HALLWAY2, STOREROOM, GYM, HALLWAY3, CLASSROOM206, JANIATORSCLOSET, HALLWAY4, HALLWAY5, HALLWAY6, CLASSROOM301, CLASSROOM303, CLASSROOM305, CLASSROOM307 };
enum en_VERBS { GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK };
enum en_NOUNS { JAN_CLOSET_DOOR, MAGNET, METER, MONEY, TEXTBOOK };//doors will be criticl, everything else meh


const int NONE = -1;//these will break everything if they're not right
const int DIRS = 4;//like no erros
const int ROOMS = 18;//but crashes
const int VERBS = 8;
const int NOUNS = 5;

//"struct" the things
struct terms
{
	string word;
	int code;
};

struct room
{
	string description;
	int exits_to_room[DIRS];
};

struct noun
{
	string word;
	string description;
	int code;
	int location;
	bool can_carry;
};


// -------------------------------------------------------------------------------------------------

//set up our rooms
void set_rooms(room *rms)
{

	//enum en_ROOMS { SCIENCELAB, CLASSROOM202, START, HALLWAY1, CAFETERIA, HALLWAY2, STOREROOM, GYM, HALLWAY3, CLASSROOM206, JANIATORSCLOSET, HALLWAY4, HALLWAY5, HALLWAY6, CLASSROOM301, CLASSROOM303, CLASSROOM305, CLASSROOM307 };
	rms[SCIENCELAB].description.assign("Science Lab 111");
	rms[SCIENCELAB].exits_to_room[NORTH] = NONE;
	rms[SCIENCELAB].exits_to_room[EAST] = NONE;
	rms[SCIENCELAB].exits_to_room[SOUTH] = START;
	rms[SCIENCELAB].exits_to_room[WEST] = NONE;

	rms[CLASSROOM202].description.assign("Classroom 202");
	rms[CLASSROOM202].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM202].exits_to_room[EAST] = NONE;
	rms[CLASSROOM202].exits_to_room[SOUTH] = HALLWAY1;
	rms[CLASSROOM202].exits_to_room[WEST] = NONE;

	rms[START].description.assign("Starting Zone/School parking lot"); //Starting zone
	rms[START].exits_to_room[NORTH] = SCIENCELAB;
	rms[START].exits_to_room[EAST] = HALLWAY1;
	rms[START].exits_to_room[SOUTH] = NONE;
	rms[START].exits_to_room[WEST] = NONE;

	rms[HALLWAY1].description.assign("Hallway 1");
	rms[HALLWAY1].exits_to_room[NORTH] = CLASSROOM202;
	rms[HALLWAY1].exits_to_room[EAST] = CAFETERIA;
	rms[HALLWAY1].exits_to_room[SOUTH] = HALLWAY2;
	rms[HALLWAY1].exits_to_room[WEST] = START;

	rms[CAFETERIA].description.assign("Cafateria");
	rms[CAFETERIA].exits_to_room[NORTH] = NONE;
	rms[CAFETERIA].exits_to_room[EAST] = NONE;
	rms[CAFETERIA].exits_to_room[SOUTH] = NONE;
	rms[CAFETERIA].exits_to_room[WEST] = HALLWAY1;

	rms[HALLWAY2].description.assign("Hallway 2");
	rms[HALLWAY2].exits_to_room[NORTH] = HALLWAY1;
	rms[HALLWAY2].exits_to_room[EAST] = STOREROOM;
	rms[HALLWAY2].exits_to_room[SOUTH] = HALLWAY3;
	rms[HALLWAY2].exits_to_room[WEST] = NONE;

	rms[STOREROOM].description.assign("School Store Room");
	rms[STOREROOM].exits_to_room[NORTH] = NONE;
	rms[STOREROOM].exits_to_room[EAST] = NONE;
	rms[STOREROOM].exits_to_room[SOUTH] = NONE;
	rms[STOREROOM].exits_to_room[WEST] = HALLWAY2;

	rms[GYM].description.assign("Gym");
	rms[GYM].exits_to_room[NORTH] = NONE;
	rms[GYM].exits_to_room[EAST] = HALLWAY3;
	rms[GYM].exits_to_room[SOUTH] = NONE;
	rms[GYM].exits_to_room[WEST] = NONE;

	rms[HALLWAY3].description.assign("Hallway 3");
	rms[HALLWAY3].exits_to_room[NORTH] = HALLWAY2;
	rms[HALLWAY3].exits_to_room[EAST] = CLASSROOM206;
	rms[HALLWAY3].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY3].exits_to_room[WEST] = GYM;

	rms[CLASSROOM206].description.assign("Classroom 206");
	rms[CLASSROOM206].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM206].exits_to_room[EAST] = NONE;
	rms[CLASSROOM206].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM206].exits_to_room[WEST] = HALLWAY3;

	rms[JANIATORSCLOSET].description.assign("Janitors Closet");
	rms[JANIATORSCLOSET].exits_to_room[NORTH] = NONE;
	rms[JANIATORSCLOSET].exits_to_room[EAST] = NONE;
	rms[JANIATORSCLOSET].exits_to_room[SOUTH] = NONE;
	rms[JANIATORSCLOSET].exits_to_room[WEST] = NONE;

	rms[HALLWAY4].description.assign("Hallway 4");
	rms[HALLWAY4].exits_to_room[NORTH] = HALLWAY3;
	rms[HALLWAY4].exits_to_room[EAST] = NONE;
	rms[HALLWAY4].exits_to_room[SOUTH] = HALLWAY5;
	rms[HALLWAY4].exits_to_room[WEST] = NONE;

	rms[HALLWAY5].description.assign("Hallway 5");
	rms[HALLWAY5].exits_to_room[NORTH] = HALLWAY4;
	rms[HALLWAY5].exits_to_room[EAST] = HALLWAY6;
	rms[HALLWAY5].exits_to_room[SOUTH] = CLASSROOM307;
	rms[HALLWAY5].exits_to_room[WEST] = NONE;

	rms[HALLWAY6].description.assign("Hallway 6");
	rms[HALLWAY6].exits_to_room[NORTH] = CLASSROOM301;
	rms[HALLWAY6].exits_to_room[EAST] = CLASSROOM303;
	rms[HALLWAY6].exits_to_room[SOUTH] = CLASSROOM305;
	rms[HALLWAY6].exits_to_room[WEST] = HALLWAY5;

	rms[CLASSROOM301].description.assign("Classroom 301");
	rms[CLASSROOM301].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM301].exits_to_room[EAST] = NONE;
	rms[CLASSROOM301].exits_to_room[SOUTH] = HALLWAY6;
	rms[CLASSROOM301].exits_to_room[WEST] = NONE;

	rms[CLASSROOM303].description.assign("Classroom 303");
	rms[CLASSROOM303].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM303].exits_to_room[EAST] = NONE;
	rms[CLASSROOM303].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM303].exits_to_room[WEST] = HALLWAY6;

	rms[CLASSROOM305].description.assign("Classroom 305");
	rms[CLASSROOM305].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM305].exits_to_room[EAST] = NONE;
	rms[CLASSROOM305].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM305].exits_to_room[WEST] = HALLWAY6;

	rms[CLASSROOM307].description.assign("Classroom 307");
	rms[CLASSROOM307].exits_to_room[NORTH] = HALLWAY5;
	rms[CLASSROOM307].exits_to_room[EAST] = NONE;
	rms[CLASSROOM307].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM307].exits_to_room[WEST] = NONE;
}

// -------------------------------------------------------------------------------------------------

//set up our directions
void set_directions(terms *dir)
{
	//enum en_DIRS { NORTH, EAST, SOUTH, WEST };
	dir[NORTH].code = NORTH;
	dir[NORTH].word = "NORTH";
	dir[EAST].code = EAST;
	dir[EAST].word = "EAST";
	dir[SOUTH].code = SOUTH;
	dir[SOUTH].word = "SOUTH";
	dir[WEST].code = WEST;
	dir[WEST].word = "WEST";
}

// -------------------------------------------------------------------------------------------------

//possible actions, will only prob end up using half of these
void set_verbs(terms *vbs)
{
	// enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};
	vbs[GET].code = GET;
	vbs[GET].word = "GET";
	vbs[DROP].code = DROP;
	vbs[DROP].word = "DROP";
	vbs[USE].code = USE;
	vbs[USE].word = "USE";
	vbs[OPEN].code = OPEN;
	vbs[OPEN].word = "OPEN";
	vbs[CLOSE].code = CLOSE;
	vbs[CLOSE].word = "CLOSE";
	vbs[EXAMINE].code = EXAMINE;
	vbs[EXAMINE].word = "EXAMINE";
	vbs[INVENTORY].code = INVENTORY;
	vbs[INVENTORY].word = "INVENTORY";
	vbs[LOOK].code = LOOK;
	vbs[LOOK].word = "LOOK";
}

// -------------------------------------------------------------------------------------------------

//things we can interact with
void set_nouns(noun *nns)
{
	//enum en_NOUNS {STORE_DOOR, MAGNET, METER, MONEY, FISHROD};


	//will need to set up many more of these
	nns[JAN_CLOSET_DOOR].word = "DOOR";
	nns[JAN_CLOSET_DOOR].code = JAN_CLOSET_DOOR;
	nns[JAN_CLOSET_DOOR].description = "a closed janiators closet door";
	nns[JAN_CLOSET_DOOR].can_carry = false;
	nns[JAN_CLOSET_DOOR].location = JANIATORSCLOSET;

	//test items? use or not use can add as needed prob for story line and such
	nns[MAGNET].word = "MAGNET";
	nns[MAGNET].code = MAGNET;
	nns[MAGNET].description = "a magnet";
	nns[MAGNET].can_carry = true;
	nns[MAGNET].location = SCIENCELAB;

	nns[METER].word = "METER";
	nns[METER].code = METER;
	nns[METER].description = "a parking meter";
	nns[METER].can_carry = false;
	nns[METER].location = START;

	nns[MONEY].word = "MONEY";
	nns[MONEY].code = MONEY;
	nns[MONEY].description = "some money";
	nns[MONEY].can_carry = true;
	nns[MONEY].location = JANIATORSCLOSET;

	nns[TEXTBOOK].word = "textbook";
	nns[TEXTBOOK].code = TEXTBOOK;
	nns[TEXTBOOK].description = "a textbook";
	nns[TEXTBOOK].can_carry = false;
	nns[TEXTBOOK].location = CLASSROOM202;
}

// -------------------------------------------------------------------------------------------------

//formating
void section_command(string Cmd, string &wd1, string &wd2)
{
	string sub_str;
	vector<string> words;
	char search = ' ';
	size_t i, j;

	for (i = 0; i < Cmd.size(); i++)
	{
		if (Cmd.at(i) != search)
		{
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}
		if (i == Cmd.size() - 1)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
		if (Cmd.at(i) == search)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
	}

	for (i = words.size() - 1; i > 0; i--)
	{
		if (words.at(i) == "")
		{
			words.erase(words.begin() + i);
		}
	}

	for (i = 0; i < words.size(); i++)
	{
		for (j = 0; j < words.at(i).size(); j++)
		{
			if (islower(words.at(i).at(j)))
			{
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}

	if (words.size() == 0)
	{
		cout << "No command given" << endl;
	}
	if (words.size() == 1)
	{
		wd1 = words.at(0);
	}
	if (words.size() == 2)
	{
		wd1 = words.at(0);
		wd2 = words.at(1);
	}
	if (words.size() > 2)
	{
		cout << "Command too long. Only type one or two words (direction or verb and noun)" << endl;
	}
}

// ----------------------------------------------------------------------------------------

//"look" function
void look_around(int loc, room *rms, terms *dir, noun *nns)
{
	int i;
	cout << "I am in a " << rms[loc].description << "." << endl;

	//Look command shows exits and reports them to the player
	for (i = 0; i < DIRS; i++)
	{
		if (rms[loc].exits_to_room[i] != NONE)
		{
			cout << "There is an exit " << dir[i].word << " to a " << rms[rms[loc].exits_to_room[i]].description << "." << endl;
		}
	}

	
	//The look command checks which objects (nouns) are in the current room and report them to the player.
	for (i = 0; i < NOUNS; i++)
	{
		if (nns[i].location == loc)
		{
			cout << "I see " << nns[i].description << "." << endl;
		}
	}
}

// ----------------------------------------------------------------------------------------

bool parser(int &loc, string wd1, string wd2, terms *dir, terms *vbs, room *rms, noun *nns)
{
	
	static bool door_state = false; //false is a closed door.
	

	int i;
	for (i = 0; i < DIRS; i++)
	{
		if (wd1 == dir[i].word)
		{
			if (rms[loc].exits_to_room[dir[i].code] != NONE)
			{
				loc = rms[loc].exits_to_room[dir[i].code];
				cout << "I am now in a " << rms[loc].description << "." << endl;
				//case for the gym to janiators closet door. will need to added for most of the other rooms
				if (loc == JANIATORSCLOSET || loc == GYM)
				{
					nns[JAN_CLOSET_DOOR].location = loc;
				}
				
				return true;
			}
			else
			{
				cout << "No exit that way." << endl;
				return true;
			}
		}
	}

	//verbs and stuff
	int NOUN_MATCH = NONE;
	int VERB_ACTION = NONE;

	for (i = 0; i < VERBS; i++)
	{
		if (wd1 == vbs[i].word)
		{
			VERB_ACTION = vbs[i].code;
			break;
		}
	}

	
	if (wd2 != "")
	{
		for (i = 0; i < NOUNS; i++)
		{
			if (wd2 == nns[i].word)
			{
				NOUN_MATCH = nns[i].code;
				break;
			}
		}
	}

	if (VERB_ACTION == NONE)
	{
		cout << "No valid command entered." << endl;
		return true;
	}

	//look verb
	if (VERB_ACTION == LOOK)
	{
		look_around(loc, rms, dir, nns);
		return true;
	}

	
	// Actions for usage of VERB OPEN
	//questions would need to be prompted in here I believe
	if (VERB_ACTION == OPEN)
	{
		if (NOUN_MATCH == JAN_CLOSET_DOOR)
		{
			if (loc == GYM || loc == JANIATORSCLOSET)
			{
				if (door_state == false)
				{
					door_state = true;
					rms[GYM].exits_to_room[SOUTH] = JANIATORSCLOSET;
					rms[JANIATORSCLOSET].exits_to_room[NORTH] = GYM;
					nns[JAN_CLOSET_DOOR].description.clear();
					nns[JAN_CLOSET_DOOR].description.assign("an open store room door");
					cout << "I have opened the door." << endl;
					return true;
				}
				else if (door_state == true)
				{
					cout << "The door is already open." << endl;
					return true;
				}
			}
			else
			{
				cout << "There is no door to open here." << endl;
				return true;
			}
		}
		else
		{
			cout << "Opening that is not possible." << endl;
			return true;
		}
	}



	//close Do we need this? prob not but hey its here
	if (VERB_ACTION == CLOSE)
	{
		if (NOUN_MATCH == JAN_CLOSET_DOOR)
		{
			if (loc == GYM || loc == JANIATORSCLOSET)
			{
				if (door_state == true)
				{
					door_state = true;
					rms[GYM].exits_to_room[SOUTH] = JANIATORSCLOSET;
					rms[JANIATORSCLOSET].exits_to_room[NORTH] = GYM;
					nns[JAN_CLOSET_DOOR].description.clear();
					nns[JAN_CLOSET_DOOR].description.assign("an open store room door");
					cout << "I have opened the door." << endl;
					return true;
				}
				else if (door_state == true)
				{
					cout << "The door is already closed." << endl;
					return true;
				}
			}
			else
			{
				cout << "There is no door to close here." << endl;
				return true;
			}
		}
		else
		{
			cout << "Closing that is not possible." << endl;
			return true;
		}
	}
	

	return false;
}

// ----------------------------------------------------------------------------------------

int main()
{
	string command;
	string word_1;
	string word_2;

	room rooms[ROOMS];
	set_rooms(rooms);

	terms directions[DIRS];
	set_directions(directions);

	terms verbs[VERBS];
	set_verbs(verbs);

	noun nouns[NOUNS];
	set_nouns(nouns);
	

	int location = START;

	while (word_1 != "QUIT")
	{
		//this needs some work
		command.clear();
		cout << "What shall I do? ";
		cout << "\nNorth \nSouth \nWest \nEast \nGET, DROP, USE, OPEN DOOR, CLOSE, EXAMINE, INVENTORY, LOOK\n";
		getline(cin, command);

		word_1.clear();
		word_2.clear();

		section_command(command, word_1, word_2);

		if (word_1 != "QUIT")
		{
			parser(location, word_1, word_2, directions, verbs, rooms, nouns);
		}
	}
	return 0;
}
