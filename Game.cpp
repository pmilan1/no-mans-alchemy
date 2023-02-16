//Title: proj2.cpp 
//Author: Milan Parmar
//Date: 3/10/2021
//Description: This is part of the No Man's Alchemy Project in CMSC 202 @ UMBC

#include "Game.h"
using namespace std;

  // Name: Game() Default Constructor
  // Desc - Builds a new game by: 
  // 1. Loads all materials and their recipes into m_materials
  // 2. Asks user for their Ship's name (store in m_myShip as m_myName)
  // 3. Copies all materials from m_materials into the Ship's material array
  // Preconditions - None
  // Postconditions - m_materials is populated
Game::Game() {
    string name;
    GameTitle();
    LoadMaterials();
    cout << "What's is the name of your ship? ";
    getline(cin, name);

    cout << endl;
    
    m_myShip.SetName(name);

    for (int i = 0; i < PROJ2_SIZE; i++) {
        m_myShip.AddMaterial(m_materials[i]);
    }
}

  // Name: LoadMaterials
  // Desc - Loads each material into m_materials from file
  // Preconditions - Requires file with valid material data
  // Postconditions - m_material is populated with material structs
void Game::LoadMaterials() {
    int counter = 0;
    string name, type, material1, material2;
    const char DELIMITER = ',';
    int quantity = 0;
    
    ifstream myfile(PROJ2_DATA);
    if (myfile.is_open()) {
        while (counter < PROJ2_SIZE) {
            getline(myfile, name, DELIMITER);
            getline(myfile, type, DELIMITER);
            getline(myfile, material1, DELIMITER);
            getline(myfile, material2);
            quantity = (type == "raw")?0:0;
            m_materials[counter] = Material(name, type, material1, material2, quantity);

            counter++;
        }
    }
    else {
        cout << "ERROR OPENING FILE" << endl;
    }
    myfile.close();
    
    cout << counter << " materials loaded." << endl;
}

  // Name: StartGame()
  // Desc - Manages the game itself including win conditions continually
  //         calling the main menu 
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5
void Game::StartGame() {
    MainMenu();
}

  // Name: DisplayMyMaterials()
  // Desc - Displays the Ship's materials (Uses GetMaterial)
  // Preconditions - Player's Ship has materials
  // Postconditions - Displays a numbered list of materials
void Game::DisplayMaterials() {
  cout << endl;
    for (int i = 0; i < PROJ2_SIZE; i++) {
      cout << i + 1 << ". ";
      cout << m_myShip.GetMaterial(i).m_name << " " << m_myShip.GetMaterial(i).m_quantity << endl;
    }
}

  // Name: MainMenu()
  // Desc - Displays and manages menu. Also checks win condition (Ship reaches S rank).
  // Preconditions - Player has a Ship
  // Postconditions - Returns number including exit
int Game::MainMenu() {
    int choice = 0;
    char rank = m_myShip.GetRank();

    cout << endl;
    
    if (rank == 'S') {
        cout << "Congrats! You won, game finished!" << endl;
    }
    else {
        cout << "What would you like to do? " << endl;
        cout << "1. Display your Ship's Materials" << endl << "2. Search for Raw Materials" << endl << "3. Attempt to Merge Materials" << endl 
            << "4. See Score" << endl << "5. Quit" << endl;
        cin >> choice;
        while (choice > 5 || choice < 1) {
            cout << "Invalid number, try again (between 1-5): ";
            cout << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;       
            }        

        if (choice == 1) {
            DisplayMaterials();
        }
        else if (choice == 2) {
            SearchMaterials();
        }
        else if (choice == 3) {
            CombineMaterials();
        }
        else if (choice == 4) {
            CalcScore();
        }
        while (choice != 5) {
	        cout << endl;
            cout << "What would you like to do? " << endl;
            cout << "1. Display your Ship's Materials" << endl << "2. Search for Raw Materials" << endl << "3. Attempt to Merge Materials" << endl 
                << "4. See Score" << endl << "5. Quit" << endl;
            cin >> choice;

            while (choice > 5 || choice < 1) {
                cout << "Invalid number, try again (between 1-5): ";
                cout << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> choice;       
                }            

            if (choice == 1) {
                DisplayMaterials();
            }
            else if (choice == 2) {
                SearchMaterials();
            }
            else if (choice == 3) {
                CombineMaterials();
            }
            else if (choice == 4) {
                CalcScore();
            }
        }
    }
    return 0;
}

  // Name: SearchMaterials()
  // Desc - Attempts to search for raw materials (must be type "raw")
  // Preconditions - Raw materials loaded
  // Postconditions - Increases quantity in Ship's possession of materials
void Game::SearchMaterials() {
    srand(time(NULL));
    int randomNum = rand() % PROJ2_SIZE;

    while (m_materials[randomNum].m_type != "raw") {
        randomNum = rand() % PROJ2_SIZE;
    }
    if (m_materials[randomNum].m_type == "raw") {
        cout << m_materials[randomNum].m_name << " found!" << endl;
        m_myShip.IncrementQuantity(m_materials[randomNum]);
    }
}

  // Name: CombineMaterials()
  // Desc - Attempts to combine known materials. If combined, quantity of material decreased
  // Preconditions - Ship is populated with materials
  // Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineMaterials() {
    int materialChoice = 0;
    int mergeIndex;
    string mergedMaterial;
    string mat1;
    string mat2;
    bool valid1 = false;
    bool valid2 = false;

    // Material 1
    cout << "Which materials would you like to merge?" << endl << "To list know materials enter -1" << endl;
    cin >> materialChoice;
    while (materialChoice < -1 || materialChoice == 0 || materialChoice > 63) {
        cout << "Invalid number, try again: ";
        cout << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> materialChoice;       
    }
    
    if (materialChoice > 0) {
        RequestMaterial(materialChoice);
        if (m_myShip.GetMaterial(materialChoice - 1).m_quantity > 0) {
            mat1 = m_myShip.GetMaterial(materialChoice - 1).m_name;
            m_myShip.DecrementQuantity(m_myShip.GetMaterial(materialChoice - 1));
            valid1 = true;
        }
        else {
            mat1 = m_myShip.GetMaterial(materialChoice - 1).m_name;
        }
    }
    while (materialChoice == -1) {
        DisplayMaterials();
        cout << "Which materials would you like to merge?" << endl << "To list know materials enter -1" << endl;
        cin >> materialChoice;

        while (materialChoice < -1 || materialChoice == 0 || materialChoice > 63) {
            cout << "Invalid number, try again: ";
            cout << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> materialChoice;       
        }        

        if (materialChoice > 0) {
            RequestMaterial(materialChoice);
            if (m_myShip.GetMaterial(materialChoice - 1).m_quantity > 0) {
                mat1 = m_myShip.GetMaterial(materialChoice - 1).m_name;
                m_myShip.DecrementQuantity(m_myShip.GetMaterial(materialChoice - 1));
                valid1 = true;
            }
            else {
                mat1 = m_myShip.GetMaterial(materialChoice - 1).m_name;
            }
        }
    }

    // Material 2
    materialChoice = 0;
    cout << "Which materials would you like to merge?" << endl << "To list know materials enter -1" << endl;
    cin >> materialChoice;

    while (materialChoice < -1 || materialChoice == 0 || materialChoice > 63) {
        cout << "Invalid number, try again: ";
        cout << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> materialChoice;       
    }    

    if (materialChoice > 0) {
        RequestMaterial(materialChoice);
        if (m_myShip.GetMaterial(materialChoice - 1).m_quantity > 0) {
            mat2 = m_myShip.GetMaterial(materialChoice - 1).m_name;
            m_myShip.DecrementQuantity(m_myShip.GetMaterial(materialChoice - 1));
            valid2 = true;
        }
        else {
            mat2 = m_myShip.GetMaterial(materialChoice - 1).m_name;
        }
    }
    while (materialChoice == -1) {
        DisplayMaterials();
        cout << "Which materials would you like to merge?" << endl << "To list know materials enter -1" << endl;
        cin >> materialChoice;

        while (materialChoice < -1 || materialChoice == 0 || materialChoice > 63) {
            cout << "Invalid number, try again: ";
            cout << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> materialChoice;       
        }        

        if (materialChoice > 0) {
            RequestMaterial(materialChoice);
            if (m_myShip.GetMaterial(materialChoice - 1).m_quantity > 0) {
                mat2 = m_myShip.GetMaterial(materialChoice - 1).m_name;
                m_myShip.DecrementQuantity(m_myShip.GetMaterial(materialChoice - 1));
                valid2 = true;
            }
            else {
                mat2 = m_myShip.GetMaterial(materialChoice - 1).m_name;
            }
        }
    }

    cout << endl;
    mergeIndex = SearchRecipes(mat1, mat2);

    if (valid1 == true && valid2 == true && mergeIndex != 0) {
        if (m_myShip.GetMaterial(mergeIndex).m_type == "unique" && m_myShip.GetMaterial(mergeIndex).m_quantity == 1) {
            cout << "Unfortunately, you have already created this unique material :(" << endl;
        }
        else {
            mergedMaterial = m_myShip.GetMaterial(mergeIndex).m_name;
            m_myShip.IncrementQuantity(m_materials[mergeIndex]);

            cout << mat1 << " combined with " << mat2 << " to make " << mergedMaterial << "!" << endl;
            cout << "You have built " << mergedMaterial << " for your ship." << endl;
        }
    }
    else if (valid1 == true && valid2 == true && mergeIndex == 0) {
        cout << "Incompatible combination." << endl;
    }
    else {
        cout << "You do not have enough " << mat1 << " or " << mat2 << " to attempt that merge." << endl;
    }
}

  // Name: RequestMaterial()
  // Desc - Requests material to use to merge
  // Preconditions - Ship has materials to try and merge
  // Postconditions - Returns integer of item selected by user
void Game::RequestMaterial(int &choice) {
    int realChoice = choice - 1;
    //    bool valid = false;

    if (m_myShip.GetMaterial(realChoice).m_quantity > 0) {
      // valid = true;
    }
}

  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings (name of item)
  // Preconditions - m_materials is populated
  // Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string mat1, string mat2) {
    int index = 0;
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (mat1 == m_materials[i].m_material1 || mat1 == m_materials[i].m_material2) {
            if (mat2 == m_materials[i].m_material1 || mat2 == m_materials[i].m_material2) {
                index = i;
            }
        }
    }
    return index;
}

  // Name: CalcScore()
  // Desc - Displays current score for Ship
  // Preconditions - Ship is populated with materials
  // Postconditions - Displays total
void Game::CalcScore() {
    int scoreCount = 0;
    char tempRank;
    char rank = m_myShip.GetRank();

    cout << endl;

    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_myShip.GetMaterial(i).m_type == "unique" && m_myShip.GetMaterial(i).m_quantity > 0) {
            scoreCount++;
        }
    }    
    if(scoreCount == 0) {
        tempRank = 'D';
    }
    else if (scoreCount == 1) {
        tempRank = 'C';
    }
    else if (scoreCount == 2) {
        tempRank = 'B';
    }
    else if (scoreCount == 3) {
        tempRank = 'A';
    }
    else if (scoreCount >= 4) {
        tempRank = 'S';
    }

    rank = m_myShip.GetRank();

    while (tempRank != rank) {
        m_myShip.IncRank();
	    rank = m_myShip.GetRank();
    }

    cout << "***The Ship***" << endl << "The Great Ship " << m_myShip.GetName() << endl << "Ship Rank: " << rank << endl;
}
