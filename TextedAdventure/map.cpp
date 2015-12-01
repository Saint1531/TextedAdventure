#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum en_DIRS { NORTH, EAST, SOUTH, WEST };

enum en_ROOMS { SCIENCELAB, CLASSROOM202, START, HALLWAY1, CAFETERIA, 
				HALLWAY2, STOREROOM, GYM, HALLWAY3, CLASSROOM206, JANIATORSCLOSET, 
				HALLWAY4, HALLWAY5, HALLWAY6, HALLWAY7, HALLWAY8, HALLWAY9, HALLWAY10,
				HALLWAY11, CLASSROOM301, CLASSROOM303, CLASSROOM305, CLASSROOM307, 
				KITCHEN, PATHWAY };

enum en_VERBS { GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK };

//DOORS FOR QUESTIONS, OBJECTS FOR STORY
enum en_NOUNS { JAN_CLOSET_DOOR,SCI_LAB_DOOR,CR202_DOOR,CAFETERIA_DOOR,KITCHEN_DOOR,SR_DOOR,
				CR206_DOOR,CR307_DOOR,CR305_DOOR,CR301_DOOR,CR303_DOOR, MAGNET, METER, MONEY, 
				TEXTBOOK, DESK, GYM_DOOR};


const int NONE = -1;//these will break everything if they're not right
const int DIRS = 4;//like no errors
const int ROOMS = 25;//but crashes
const int VERBS = 8;
const int NOUNS = 17;

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

	//enum en_ROOMS { SCIENCELAB, CLASSROOM202, START, HALLWAY1, CAFETERIA, HALLWAY2, STOREROOM, GYM, 
	//HALLWAY3, CLASSROOM206, JANIATORSCLOSET, HALLWAY4, HALLWAY5, HALLWAY6, CLASSROOM301, CLASSROOM303, 
	//CLASSROOM305, CLASSROOM307 };
	rms[START].description.assign("School parking lot"); //Starting zone
	rms[START].exits_to_room[NORTH] = NONE;
	rms[START].exits_to_room[EAST] = NONE;
	rms[START].exits_to_room[SOUTH] = PATHWAY;
	rms[START].exits_to_room[WEST] = NONE;

	rms[PATHWAY].description.assign("Pathway to the science lab"); //Starting zone
	rms[PATHWAY].exits_to_room[NORTH] = START;
	rms[PATHWAY].exits_to_room[EAST] = NONE;
	rms[PATHWAY].exits_to_room[SOUTH] = NONE;
	rms[PATHWAY].exits_to_room[WEST] = NONE;

	rms[SCIENCELAB].description.assign("Science Lab 111");
	rms[SCIENCELAB].exits_to_room[NORTH] = NONE;
	rms[SCIENCELAB].exits_to_room[EAST] = NONE;
	rms[SCIENCELAB].exits_to_room[SOUTH] = HALLWAY1;
	rms[SCIENCELAB].exits_to_room[WEST] = NONE;

	rms[CLASSROOM202].description.assign("Classroom 202");
	rms[CLASSROOM202].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM202].exits_to_room[EAST] = NONE;
	rms[CLASSROOM202].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM202].exits_to_room[WEST] = HALLWAY2;

	rms[CLASSROOM206].description.assign("Classroom 206");
	rms[CLASSROOM206].exits_to_room[NORTH] = HALLWAY3;
	rms[CLASSROOM206].exits_to_room[EAST] = NONE;
	rms[CLASSROOM206].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM206].exits_to_room[WEST] = NONE;

	rms[CLASSROOM301].description.assign("Classroom 301");
	rms[CLASSROOM301].exits_to_room[NORTH] = HALLWAY7;
	rms[CLASSROOM301].exits_to_room[EAST] = NONE;
	rms[CLASSROOM301].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM301].exits_to_room[WEST] = NONE;

	rms[CLASSROOM303].description.assign("Classroom 303");
	rms[CLASSROOM303].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM303].exits_to_room[EAST] = NONE;
	rms[CLASSROOM303].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM303].exits_to_room[WEST] = HALLWAY8;

	rms[CLASSROOM305].description.assign("Classroom 305");
	rms[CLASSROOM305].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM305].exits_to_room[EAST] = NONE;
	rms[CLASSROOM305].exits_to_room[SOUTH] = HALLWAY9;
	rms[CLASSROOM305].exits_to_room[WEST] = NONE;

	rms[CLASSROOM307].description.assign("Classroom 307");
	rms[CLASSROOM307].exits_to_room[NORTH] = NONE;
	rms[CLASSROOM307].exits_to_room[EAST] = NONE;
	rms[CLASSROOM307].exits_to_room[SOUTH] = NONE;
	rms[CLASSROOM307].exits_to_room[WEST] = HALLWAY10;

	rms[KITCHEN].description.assign("Kitchen");
	rms[KITCHEN].exits_to_room[NORTH] = NONE;
	rms[KITCHEN].exits_to_room[EAST] = HALLWAY6;
	rms[KITCHEN].exits_to_room[SOUTH] = NONE;
	rms[KITCHEN].exits_to_room[WEST] = NONE;

	rms[CAFETERIA].description.assign("Cafateria");
	rms[CAFETERIA].exits_to_room[NORTH] = NONE;
	rms[CAFETERIA].exits_to_room[EAST] = NONE;
	rms[CAFETERIA].exits_to_room[SOUTH] = HALLWAY3;
	rms[CAFETERIA].exits_to_room[WEST] = HALLWAY4;

	rms[STOREROOM].description.assign("School Store Room");
	rms[STOREROOM].exits_to_room[NORTH] = NONE;
	rms[STOREROOM].exits_to_room[EAST] = NONE;
	rms[STOREROOM].exits_to_room[SOUTH] = HALLWAY5;
	rms[STOREROOM].exits_to_room[WEST] = NONE;

	rms[GYM].description.assign("Gym");
	rms[GYM].exits_to_room[NORTH] = HALLWAY11;
	rms[GYM].exits_to_room[EAST] = NONE;
	rms[GYM].exits_to_room[SOUTH] = NONE;
	rms[GYM].exits_to_room[WEST] = NONE;

	rms[JANIATORSCLOSET].description.assign("Janitors Closet");
	rms[JANIATORSCLOSET].exits_to_room[NORTH] = NONE;
	rms[JANIATORSCLOSET].exits_to_room[EAST] = NONE;
	rms[JANIATORSCLOSET].exits_to_room[SOUTH] = NONE;
	rms[JANIATORSCLOSET].exits_to_room[WEST] = NONE;

	rms[HALLWAY1].description.assign("Hallway 1");
	rms[HALLWAY1].exits_to_room[NORTH] = SCIENCELAB;
	rms[HALLWAY1].exits_to_room[EAST] = NONE;
	rms[HALLWAY1].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY1].exits_to_room[WEST] = NONE;

	rms[HALLWAY2].description.assign("Hallway 2");
	rms[HALLWAY2].exits_to_room[NORTH] = NONE;
	rms[HALLWAY2].exits_to_room[EAST] = NONE;
	rms[HALLWAY2].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY2].exits_to_room[WEST] = CLASSROOM202;

	rms[HALLWAY3].description.assign("Hallway 3");
	rms[HALLWAY3].exits_to_room[NORTH] = NONE;
	rms[HALLWAY3].exits_to_room[EAST] = NONE;
	rms[HALLWAY3].exits_to_room[SOUTH] = CLASSROOM206;
	rms[HALLWAY3].exits_to_room[WEST] = NONE;

	rms[HALLWAY4].description.assign("Hallway 4");
	rms[HALLWAY4].exits_to_room[NORTH] = NONE;
	rms[HALLWAY4].exits_to_room[EAST] = NONE;
	rms[HALLWAY4].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY4].exits_to_room[WEST] = CAFETERIA;

	rms[HALLWAY5].description.assign("Hallway 5");
	rms[HALLWAY5].exits_to_room[NORTH] = STOREROOM;
	rms[HALLWAY5].exits_to_room[EAST] = NONE;
	rms[HALLWAY5].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY5].exits_to_room[WEST] = NONE;

	rms[HALLWAY6].description.assign("Hallway 6");
	rms[HALLWAY6].exits_to_room[NORTH] = NONE;
	rms[HALLWAY6].exits_to_room[EAST] = NONE;
	rms[HALLWAY6].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY6].exits_to_room[WEST] = KITCHEN;

	rms[HALLWAY7].description.assign("Hallway 7");
	rms[HALLWAY7].exits_to_room[NORTH] = NONE;
	rms[HALLWAY7].exits_to_room[EAST] = NONE;
	rms[HALLWAY7].exits_to_room[SOUTH] = CLASSROOM301;
	rms[HALLWAY7].exits_to_room[WEST] = NONE;

	rms[HALLWAY8].description.assign("Hallway 8");
	rms[HALLWAY8].exits_to_room[NORTH] = NONE;
	rms[HALLWAY8].exits_to_room[EAST] = NONE;
	rms[HALLWAY8].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY8].exits_to_room[WEST] = CLASSROOM303;

	rms[HALLWAY9].description.assign("Hallway 9");
	rms[HALLWAY9].exits_to_room[NORTH] = CLASSROOM305;
	rms[HALLWAY9].exits_to_room[EAST] = NONE;
	rms[HALLWAY9].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY9].exits_to_room[WEST] = NONE;

	rms[HALLWAY10].description.assign("Hallway 10");
	rms[HALLWAY10].exits_to_room[NORTH] = NONE;
	rms[HALLWAY10].exits_to_room[EAST] = NONE;
	rms[HALLWAY10].exits_to_room[SOUTH] = NONE;
	rms[HALLWAY10].exits_to_room[WEST] = CLASSROOM307;

	rms[HALLWAY11].description.assign("Hallway 11");
	rms[HALLWAY11].exits_to_room[NORTH] = NONE;
	rms[HALLWAY11].exits_to_room[EAST] = NONE;
	rms[HALLWAY11].exits_to_room[SOUTH] = GYM;
	rms[HALLWAY11].exits_to_room[WEST] = NONE;


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

	//enum en_NOUNS {
	//	JAN_CLOSET_DOOR, SCI_LAB_DOOR, CR202_DOOR, CAFETERIA_DOOR, KITCHEN_DOOR, SR_DOOR,
	//	CR206_DOOR, CR307_DOOR, CR305_DOOR, CR301_DOOR, CR303_DOOR, MAGNET, METER, MONEY, TEXTBOOK};

	nns[JAN_CLOSET_DOOR].word = "DOOR";
	nns[JAN_CLOSET_DOOR].code = JAN_CLOSET_DOOR;
	nns[JAN_CLOSET_DOOR].description = "a closed janiators closet door";
	nns[JAN_CLOSET_DOOR].can_carry = false;
	nns[JAN_CLOSET_DOOR].location = JANIATORSCLOSET;

	nns[SCI_LAB_DOOR].word = "DOOR";
	nns[SCI_LAB_DOOR].code = SCI_LAB_DOOR;
	nns[SCI_LAB_DOOR].description = "a closed science lab door";
	nns[SCI_LAB_DOOR].can_carry = false;
	nns[SCI_LAB_DOOR].location = PATHWAY;

	nns[CR202_DOOR].word = "DOOR";
	nns[CR202_DOOR].code = CR202_DOOR;
	nns[CR202_DOOR].description = "classroxom 202's door";
	nns[CR202_DOOR].can_carry = false;
	nns[CR202_DOOR].location = CLASSROOM202;

	nns[CR206_DOOR].word = "DOOR";
	nns[CR206_DOOR].code = CR206_DOOR;
	nns[CR206_DOOR].description = "classroom 206's door";
	nns[CR206_DOOR].can_carry = false;
	nns[CR206_DOOR].location = CLASSROOM206;

	nns[CR301_DOOR].word = "DOOR";
	nns[CR301_DOOR].code = CR301_DOOR;
	nns[CR301_DOOR].description = "classroom 301's door";
	nns[CR301_DOOR].can_carry = false;
	nns[CR301_DOOR].location = CLASSROOM301;

	nns[CR303_DOOR].word = "DOOR";
	nns[CR303_DOOR].code = CR303_DOOR;
	nns[CR303_DOOR].description = "classroom 303's door";
	nns[CR303_DOOR].can_carry = false;
	nns[CR303_DOOR].location = CLASSROOM303;

	nns[CR305_DOOR].word = "DOOR";
	nns[CR305_DOOR].code = CR305_DOOR;
	nns[CR305_DOOR].description = "classroom 305's door";
	nns[CR305_DOOR].can_carry = false;
	nns[CR305_DOOR].location = CLASSROOM305;

	nns[CR307_DOOR].word = "DOOR";
	nns[CR307_DOOR].code = CR307_DOOR;
	nns[CR307_DOOR].description = "classroom 307's door";
	nns[CR307_DOOR].can_carry = false;
	nns[CR307_DOOR].location = CLASSROOM307;

	nns[SR_DOOR].word = "DOOR";
	nns[SR_DOOR].code = SR_DOOR;
	nns[SR_DOOR].description = "a closed store room door";
	nns[SR_DOOR].can_carry = false;
	nns[SR_DOOR].location = STOREROOM;

	nns[KITCHEN_DOOR].word = "DOOR";
	nns[KITCHEN_DOOR].code = KITCHEN_DOOR;
	nns[KITCHEN_DOOR].description = "a closed kitchen door";
	nns[KITCHEN_DOOR].can_carry = false;
	nns[KITCHEN_DOOR].location = KITCHEN;

	nns[GYM_DOOR].word = "DOOR";
	nns[GYM_DOOR].code = GYM_DOOR;
	nns[GYM_DOOR].description = "a closed GYM door";
	nns[GYM_DOOR].can_carry = false;
	nns[GYM_DOOR].location = GYM;

	nns[CAFETERIA_DOOR].word = "DOOR";
	nns[CAFETERIA_DOOR].code = CAFETERIA_DOOR;
	nns[CAFETERIA_DOOR].description = "a closed cafeteria door";
	nns[CAFETERIA_DOOR].can_carry = false;
	nns[CAFETERIA_DOOR].location = CAFETERIA;

	//Using for story line
	nns[MAGNET].word = "MAGNET";
	nns[MAGNET].code = MAGNET;
	nns[MAGNET].description = "A large magnet sits in the center of the room magnet.\nA hum is emanating from the magnet and all the metal objects in the room to be shifted twords the large magnet.\nThe purpose of such a large magnet is puzzling to you and why its running with no one watching it.";
	nns[MAGNET].can_carry = false;
	nns[MAGNET].location = SCIENCELAB;

	nns[METER].word = "METER";
	nns[METER].code = METER;
	nns[METER].description = "A large quanity of parking meters sit in a row in the parking lot. /nWhat kind of school has parking meters?";
	nns[METER].can_carry = false;
	nns[METER].location = START;

	nns[MONEY].word = "MONEY";
	nns[MONEY].code = MONEY;
	nns[MONEY].description = "A huge amount of money in various denominations lie in a pile in the corner. /nNever seen that before in a Janiators Closet.";
	nns[MONEY].can_carry = true;
	nns[MONEY].location = JANIATORSCLOSET;

	nns[TEXTBOOK].word = "textbook";
	nns[TEXTBOOK].code = TEXTBOOK;
	nns[TEXTBOOK].description = "A weird looking textbook lies on a desk in the back of the room. /nThe language is not one you've ever seen before. /nWhere am I?";
	nns[TEXTBOOK].can_carry = false;
	nns[TEXTBOOK].location = CLASSROOM202;

	nns[DESK].word = "desk";
	nns[DESK].code = DESK;
	nns[DESK].description = "The room is nearly full with desks in perfect rows and stacked one on top of the other all the way to the ceiling. /nThe desks are so close together that it's nearly impossible to navigate anywhere of meaning in the class room.";
	nns[DESK].can_carry = false;
	nns[DESK].location = CLASSROOM206;

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
	cout << "I am in " << rms[loc].description << "." << endl;

	//Look command shows exits and reports them to the player
	for (i = 0; i < DIRS; i++)
	{
		if (rms[loc].exits_to_room[i] != NONE)
		{
			cout << "There is an exit " << dir[i].word << " to " << rms[rms[loc].exits_to_room[i]].description << "." << endl;
		}
	}

	
}
// ----------------------------------------------------------------------------------------

//"examine" function
void examine_objects(int loc,  noun *nns)
{
	int i;
	
	//The examine command checks which objects (nouns) are in the current room and report them to the player.
	for (i = 0; i < NOUNS; i++)
	{
		if (nns[i].location == loc)
		{
			cout << "" << nns[i].description << "." << endl;
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
				cout << "I am now in " << rms[loc].description << "." << endl;
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

	//examine verb
	if (VERB_ACTION == EXAMINE)
	{
		examine_objects(loc,nns);
		return true;
	}
	
	// Actions for usage of VERB OPEN
	//questions would need to be prompted in here I believe
	if (VERB_ACTION == OPEN)
	{





		//SCI LAB
		if (NOUN_MATCH == SCIENCELAB)
		{
			if (loc == PATHWAY || loc == SCIENCELAB)
			{
				if (door_state == false)
				{
					door_state = true;
					rms[PATHWAY].exits_to_room[SOUTH] = SCIENCELAB;
					rms[SCIENCELAB].exits_to_room[NORTH] = PATHWAY;
					nns[SCI_LAB_DOOR].description.clear();
					nns[SCI_LAB_DOOR].description.assign("an open science lab door");
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

		//JANIATORS CLOSET
		if (NOUN_MATCH == JANIATORSCLOSET)
		{
			if (loc == HALLWAY11 || loc == JANIATORSCLOSET)
			{
				if (door_state == false)
				{
					door_state = true;
					rms[HALLWAY11].exits_to_room[NORTH] = JANIATORSCLOSET;
					rms[JANIATORSCLOSET].exits_to_room[SOUTH] = HALLWAY11;
					nns[JAN_CLOSET_DOOR].description.clear();
					nns[JAN_CLOSET_DOOR].description.assign("an open janiators closet door");
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

		//classroom 202
		if(NOUN_MATCH == CLASSROOM202)
		{
			if (loc == HALLWAY1 || loc == CLASSROOM202)
			{
				if (door_state == false)
				{
					door_state = true;
					rms[HALLWAY1].exits_to_room[SOUTH] = CLASSROOM202;
					rms[CLASSROOM202].exits_to_room[NORTH] = HALLWAY1;
					nns[CR202_DOOR].description.clear();
					nns[CR202_DOOR].description.assign("an open class room door");
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

		//classroom 206
		if (NOUN_MATCH == CLASSROOM206)
		{
			if (loc == HALLWAY2 || loc == CLASSROOM202)
			{
				if (door_state == false)
				{
					door_state = true;
					rms[HALLWAY2].exits_to_room[NORTH] = CLASSROOM206;
					rms[CLASSROOM202].exits_to_room[SOUTH] = HALLWAY2;
					nns[CR206_DOOR].description.clear();
					nns[CR206_DOOR].description.assign("an open class room door");
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

	//classroom 301
	if (NOUN_MATCH == CLASSROOM301)
	{
		if (loc == HALLWAY6 || loc == CLASSROOM301)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY6].exits_to_room[NORTH] = CLASSROOM301;
				rms[CLASSROOM301].exits_to_room[SOUTH] = HALLWAY6;
				nns[CR301_DOOR].description.clear();
				nns[CR301_DOOR].description.assign("an open class room door");
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
	
	//classroom 303
	if (NOUN_MATCH == CLASSROOM303)
	{
		if (loc == HALLWAY7 || loc == CLASSROOM303)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY7].exits_to_room[NORTH] = CLASSROOM303;
				rms[CLASSROOM303].exits_to_room[SOUTH] = HALLWAY7;
				nns[CR303_DOOR].description.clear();
				nns[CR303_DOOR].description.assign("an open class room door");
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


	//classroom 305
	if (NOUN_MATCH == CLASSROOM305)
	{
		if (loc == HALLWAY8 || loc == CLASSROOM305)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY8].exits_to_room[SOUTH] = CLASSROOM305;
				rms[CLASSROOM305].exits_to_room[NORTH] = HALLWAY8;
				nns[CR305_DOOR].description.clear();
				nns[CR305_DOOR].description.assign("an open class room door");
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

	//classroom 307
	if (NOUN_MATCH == CLASSROOM307)
	{
		if (loc == HALLWAY9 || loc == CLASSROOM307)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY9].exits_to_room[SOUTH] = CLASSROOM307;
				rms[CLASSROOM307].exits_to_room[NORTH] = HALLWAY9;
				nns[CR307_DOOR].description.clear();
				nns[CR307_DOOR].description.assign("an open class room door");
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

	//STORE ROOM
	if (NOUN_MATCH == STOREROOM)
	{
		if (loc == HALLWAY4 || loc == STOREROOM)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY4].exits_to_room[SOUTH] = STOREROOM;
				rms[STOREROOM].exits_to_room[NORTH] = HALLWAY4;
				nns[SR_DOOR].description.clear();
				nns[SR_DOOR].description.assign("an open store room door");
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

	//CAFETERIA
	if (NOUN_MATCH == CAFETERIA)
	{
		if (loc == HALLWAY3 || loc == CAFETERIA)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY3].exits_to_room[NORTH] = CAFETERIA;
				rms[CAFETERIA].exits_to_room[SOUTH] = HALLWAY3;
				nns[CAFETERIA_DOOR].description.clear();
				nns[CAFETERIA_DOOR].description.assign("an open store room door");
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

	//GYM
	if (NOUN_MATCH == GYM)
	{
		if (loc == HALLWAY10 || loc == GYM)
		{
			if (door_state == false)
			{
				door_state = true;
				rms[HALLWAY10].exits_to_room[NORTH] = GYM;
				rms[GYM].exits_to_room[SOUTH] = HALLWAY10;
				nns[GYM_DOOR].description.clear();
				nns[GYM_DOOR].description.assign("an open GYM door");
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


	//close Do we need this? prob not but hey its here for one door
	/*
	if (VERB_ACTION == CLOSE)
	{
		if (NOUN_MATCH == HALLWAY11)
		{
			if (loc == HALLWAY11 || loc == JANIATORSCLOSET)
			{
				if (door_state == true)
				{
					door_state = true;
					rms[HALLWAY11].exits_to_room[NORTH] = JANIATORSCLOSET;
					rms[JANIATORSCLOSET].exits_to_room[SOUTH] = HALLWAY11;
					nns[JAN_CLOSET_DOOR].description.clear();
					nns[JAN_CLOSET_DOOR].description.assign("an open janiator's closet door");
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
	*/

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
		//this needs some work for a menu, And I keep putting it off
		command.clear();
		cout << "What shall I do? ";
		cout << "\nNorth \nSouth \nWest \nEast \nOPEN DOOR, EXAMINE, LOOK\n";
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
