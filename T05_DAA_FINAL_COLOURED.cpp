





#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>
#include <thread>
#include<unordered_map>
#include<math.h>
#include<climits>
#include<cstdlib>
#include<iomanip>
#include<numeric>
#include<algorithm>
#include <map>
#include <climits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <conio.h> // For getch() on Windows


//----

//===============================
//AIR POLLUTION

//D:\\DAA Airawar Project\\pollution.txt


using namespace std;

//----------------------------------------

// Utility Functions
namespace Utils {
    void printLine(int length = 50, char ch = '-') {
        cout << string(length, ch) << endl;
    }
}

// Structure to hold sewage tank data
struct Tank {
    int id;
    double currentLevel;   // Current sewage level
    double maxCapacity;    // Maximum capacity of the tank
    string status;         // Status of the tank (e.g., "Normal", "Maintenance Required")
    time_t lastMaintenanceDate;  // Last maintenance date
    int maintenanceIntervalDays; // Interval (in days) for next maintenance
    vector<double> usageHistory; // Historical usage records
};

void generateRandomLevels(vector<Tank>& tanks) {
    srand(static_cast<unsigned>(time(0)));
    for (auto& tank : tanks) {
        tank.currentLevel = static_cast<double>(rand() % static_cast<int>(tank.maxCapacity + 1));
    }
    cout << "Random levels generated for all tanks.\n";
}

void checkSewageLevels(const vector<Tank>& tanks, double threshold) {
    for (const auto& tank : tanks) {
        if (tank.currentLevel >= threshold * tank.maxCapacity) {
            cout << "Alert: Tank " << tank.id << " is at " << tank.currentLevel
                 << " which exceeds the threshold of " << threshold * tank.maxCapacity << endl;
        }
    }
}

void printTankDetails(const vector<Tank>& tanks) {
    cout << "Sewage Tank Details:\n";
    for (const auto& tank : tanks) {
        cout << "Tank ID: " << tank.id << ", Current Level: " << tank.currentLevel
             << ", Max Capacity: " << tank.maxCapacity << ", Status: " << tank.status << endl;
    }
}

void resetTankLevels(vector<Tank>& tanks)
{
    for (auto& tank : tanks)
        {
        tank.currentLevel = 0.0;
    }
    cout << "All tank levels have been reset to 0.\n";
}

Tank findHighestLevelTank(const vector<Tank>& tanks) {
    return *max_element(tanks.begin(), tanks.end(), [](const Tank& a, const Tank& b) {
        return a.currentLevel < b.currentLevel;
    });
}

void inputSewageLevels(vector<Tank>& tanks) {
    for (auto& tank : tanks) {
        cout << "Enter current level for Tank " << tank.id << ": ";
        cin >> tank.currentLevel;
    }
}

void simulateOverflow(vector<Tank>& tanks, double overflowAmount) {
    for (auto& tank : tanks) {
        if (tank.currentLevel > overflowAmount) {
            cout << "Overflow alert: Tank " << tank.id << " has overflowed!\n";
        }
        else
        {
            cout<<tank.id<<"is still need to be filled \n";
        }
    }
}

void checkAndUpdateStatus(vector<Tank>& tanks, double threshold) {
    for (auto& tank : tanks) {
        if (tank.currentLevel >= threshold * tank.maxCapacity) {
            tank.status = "Maintenance Required";
        } else {
            tank.status = "Normal";
        }
    }
    cout << "Tank statuses have been updated.\n";
}

void scheduleMaintenance(vector<Tank>& tanks) {
    for (auto& tank : tanks) {
        if (tank.status == "Maintenance Required") {
            cout << "Scheduling maintenance for Tank " << tank.id << "...\n";
            tank.currentLevel = 0.0;
            tank.status = "Normal";
            tank.lastMaintenanceDate = time(0);  // Set current time as the maintenance date
            cout << "Maintenance completed for Tank " << tank.id << ".\n";
        }
    }
}

void generateReport(const vector<Tank>& tanks) {
    cout << "\nSewage System Report:\n";
    for (const auto& tank : tanks) {
        cout << "Tank ID: " << tank.id
             << ", Current Level: " << tank.currentLevel
             << ", Max Capacity: " << tank.maxCapacity
             << ", Status: " << tank.status << "\n";
    }
}

void recordTankUsage(vector<Tank>& tanks, double usageAmount) {
    for (auto& tank : tanks) {
        tank.usageHistory.push_back(usageAmount);
        tank.currentLevel += usageAmount;
        if (tank.currentLevel > tank.maxCapacity) {
            cout << "Overflow alert: Tank " << tank.id << " has overflowed due to high usage!\n";
        }
    }
}

void checkMaintenanceDue(vector<Tank>& tanks) {
    time_t currentTime = time(0);  // Current time in seconds
    for (auto& tank : tanks) {
        double daysSinceMaintenance = difftime(currentTime, tank.lastMaintenanceDate) / (60 * 60 * 24);
        if (daysSinceMaintenance >= tank.maintenanceIntervalDays) {
            cout << "Tank " << tank.id << " requires maintenance. It's overdue by " << daysSinceMaintenance << " days.\n";
        }
    }
}

void generateTankUsageStats(const vector<Tank>& tanks) {
    double totalLevel = 0.0;
    double maxLevel = 0.0;
    int maxLevelTankId = -1;
    for (const auto& tank : tanks) {
        totalLevel += tank.currentLevel;
        if (tank.currentLevel > maxLevel) {
            maxLevel = tank.currentLevel;
            maxLevelTankId = tank.id;
        }
    }
    double avgLevel = totalLevel / tanks.size();
    cout << "Average tank level: " << avgLevel << "\n";
    cout << "Maximum tank level: " << maxLevel << " (Tank ID " << maxLevelTankId << ")\n";
}

void alertForEmptyTanks(const vector<Tank>& tanks, double emptyThreshold) {
    for (const auto& tank : tanks) {
        if (tank.currentLevel <= emptyThreshold * tank.maxCapacity) {
            cout << "Alert: Tank " << tank.id << " is almost empty! Current level: " << tank.currentLevel << "\n";
        }
    }
}

void simulateSewageTreatment(vector<Tank>& tanks, double treatmentRate) {
    for (auto& tank : tanks) {
        tank.currentLevel -= treatmentRate;
        if (tank.currentLevel < 0) {
            tank.currentLevel = 0;
        }
        cout << "Tank " << tank.id << " treated, new level: " << tank.currentLevel << "\n";
    }
}

void findMostAndLeastUsedTanks(const vector<Tank>& tanks) {
    int mostUsedTankId = -1;
    double mostUsage = 0.0;
    int leastUsedTankId = -1;
    double leastUsage = numeric_limits<double>::max();

    for (const auto& tank : tanks) {
        double totalUsage = accumulate(tank.usageHistory.begin(), tank.usageHistory.end(), 0.0);
        if (totalUsage > mostUsage) {
            mostUsage = totalUsage;
            mostUsedTankId = tank.id;
        }
        if (totalUsage < leastUsage) {
            leastUsage = totalUsage;
            leastUsedTankId = tank.id;
        }
    }
    cout << "Most used tank: ID " << mostUsedTankId << ", Total Usage: " << mostUsage << "\n";
    cout << "Least used tank: ID " << leastUsedTankId << ", Total Usage: " << leastUsage << "\n";
}

void displayStatusSummary(const vector<Tank>& tanks) {
    int normalCount = 0;
    int maintenanceCount = 0;

    for (const auto& tank : tanks) {
        if (tank.status == "Normal") {
            normalCount++;
        } else if (tank.status == "Maintenance Required") {
            maintenanceCount++;
        }
    }

    cout << "Status Summary:\n";
    cout << "Normal: " << normalCount << " tanks\n";
    cout << "Maintenance Required: " << maintenanceCount << " tanks\n";
}

void deleteTank(vector<Tank>& tanks, int tankId) {
    auto it = remove_if(tanks.begin(), tanks.end(), [tankId](const Tank& tank) {
        return tank.id == tankId;
    });
    if (it != tanks.end()) {
        tanks.erase(it, tanks.end());
        cout << "Tank " << tankId << " has been removed from the system.\n";
    } else {
        cout << "Tank " << tankId << " not found.\n";
    }
}

void run() {
    // ANSI escape codes for colors
    const string white = "\033[1;37m";     // White
    const string red = "\033[1;31m";        // Red
    const string pink = "\033[1;35m";       // Pink
    const string reset = "\033[0m";         // Reset formatting

    vector<Tank> tanks = {
        {1, 0.0, 100.0, "Normal", time(0), 30, {}},
        {2, 0.0, 100.0, "Normal", time(0), 30, {}},
        {3, 0.0, 100.0, "Normal", time(0), 30, {}}
    };

    int choice;
    do {
        cout << "----------\n";
        cout << "  Menu    \n";
        cout << "----------\n";

        // Menu items in White
        cout << white << "\n1. Generate Random Levels\n";
        cout << "2. Check Sewage Levels\n";
        cout << "3. Print Tank Details\n";
        cout << "4. Reset Tank Levels\n";
        cout << "5. Find Highest Level Tank\n";
        cout << "6. Input Sewage Levels\n";
        cout << "7. Simulate Overflow\n";
        cout << "8. Check and Update Status\n";
        cout << "9. Schedule Maintenance\n";
        cout << "10. Generate Report\n";
        cout << "11. Generate Tank Usage Stats\n";
        cout << "12. Alert for Empty Tanks\n";
        cout << "13. Simulate Sewage Treatment\n";
        cout << "14. Display Status Summary\n";

        // Exit option in Red
        cout << red << "0. Exit\n" << reset;

        // Input prompt in Pink
        cout << pink << "\nEnter your choice: " << reset;
        cout << pink << "\n " << reset;

        cin >> choice;

        switch (choice) {
            case 1:
                generateRandomLevels(tanks);
                break;
            case 2: {
                double threshold;
                cout << "Enter threshold (as a fraction of max capacity): ";
                cin >> threshold;
                checkSewageLevels(tanks, threshold);
                break;
            }
            case 3:
                printTankDetails(tanks);
                break;
            case 4:
                resetTankLevels(tanks);
                break;
            case 5: {
                Tank highestTank = findHighestLevelTank(tanks);
                cout << "Highest Level Tank: ID " << highestTank.id << ", Level " << highestTank.currentLevel << endl;
                break;
            }
            case 6:
                inputSewageLevels(tanks);
                break;
            case 7: {
                double overflowAmount;
                cout << "Enter overflow amount: ";
                cin >> overflowAmount;
                simulateOverflow(tanks, overflowAmount);
                break;
            }
            case 8: {
                double threshold;
                cout << "Enter threshold (as a fraction of max capacity): ";
                cin >> threshold;
                checkAndUpdateStatus(tanks, threshold);
                break;
            }
            case 9:
                scheduleMaintenance(tanks);
                break;
            case 10:
                generateReport(tanks);
                break;
            case 210: {
                double usageAmount;
                cout << "Enter sewage usage amount: ";
                cin >> usageAmount;
                recordTankUsage(tanks, usageAmount);
                break;
            }
            case 201:
                checkMaintenanceDue(tanks);
                break;
            case 11:
                generateTankUsageStats(tanks);
                break;
            case 12: {
                double emptyThreshold;
                cout << "Enter empty threshold (as a fraction of max capacity): ";
                cin >> emptyThreshold;
                alertForEmptyTanks(tanks, emptyThreshold);
                break;
            }
            case 13: {
                double treatmentRate;
                cout << "Enter sewage treatment rate: ";
                cin >> treatmentRate;
                simulateSewageTreatment(tanks, treatmentRate);
                break;
            }
            case 101:
                findMostAndLeastUsedTanks(tanks);
                break;
            case 14:
                displayStatusSummary(tanks);
                break;
            case 100: {
                int tankId;
                cout << "Enter tank ID to delete: ";
                cin >> tankId;
                deleteTank(tanks, tankId);
                break;
            }
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

//----------------------------------------


// Function Prototypes
void login();
void mainMenu();
void waterPollutionMonitoring();
void dataCollectionModule22();
void waterQualityIndexCalculation();
void pollutantDetectionAndClassification();
void realTimeMonitoringAndAlertSystem();
void contaminationSourceTracking();
void pollutionSpreadPrediction();
void classificationOfWaterQuality();
void forecastFutureWaterQuality();
void remediationRecommendation();
void visualizationAndReporting();

//--------------------------------

// PollutionData structure
struct PollutionData {
    string cityId, cityName, monitoringStationName, pollutantName, alertMessage;
    int population, dangerousLevel;
    double distanceFromState;

    PollutionData() {}

    PollutionData(string id, string name, int pop, string station, double dist, string pollutant, int dangerLevel, string alert)
        : cityId(id), cityName(name), population(pop), monitoringStationName(station), distanceFromState(dist),
          pollutantName(pollutant), dangerousLevel(dangerLevel), alertMessage(alert) {}

    string toCSV() const {
        stringstream ss;
        ss << cityId << "," << cityName << "," << population << "," << monitoringStationName << "," << distanceFromState
           << "," << pollutantName << "," << dangerousLevel << "," << alertMessage;
        return ss.str();
    }

    static PollutionData fromCSV(const string &line) {
        stringstream ss(line);
        string id, name, station, pollutant, alert;
        int pop, dangerLevel;
        double dist;
        getline(ss, id, ',');
        getline(ss, name, ',');
        ss >> pop; ss.ignore();
        getline(ss, station, ',');
        ss >> dist; ss.ignore();
        getline(ss, pollutant, ',');
        ss >> dangerLevel; ss.ignore();
        getline(ss, alert);
        return PollutionData(id, name, pop, station, dist, pollutant, dangerLevel, alert);
    }
};

// Global variables
map<string, vector<PollutionData>> stateCityData;

// Function declarations
void readFromFileAndAddCities(const string &filename);
void addCityToState();
void checkPollutionThreshold(const string &state);
void userDefinedThresholdDetection(const string &state);
void displayCityData(const string &state);
void listStates();
void viewStateData(unordered_map<int, string> mp);
string findCityWithMaxPollution(const string &state);
string findMinPollutionCity(const string &state);
void saveData(const string &filename);
void loadData(const string &filename);
void mainMenu();

void readFromFileAndAddCities(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open file: " << filename << "\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string state, cityId, cityName, stationName, pollutantName, alertMessage;
        int population, dangerousLevel;
        double distance;
        getline(ss, state, ',');
        getline(ss, cityId, ',');
        getline(ss, cityName, ',');
        ss >> population; ss.ignore();
        getline(ss, stationName, ',');
        ss >> distance; ss.ignore();
        getline(ss, pollutantName, ',');
        ss >> dangerousLevel; ss.ignore();
        getline(ss, alertMessage);
        PollutionData newCity(cityId, cityName, population, stationName, distance, pollutantName, dangerousLevel, alertMessage);
        stateCityData[state].push_back(newCity);
    }

    file.close();
    cout << "Cities data loaded successfully from " << filename << "\n";
}

void addCityToState() {
    string state, cityId, cityName, stationName, pollutantName, alertMessage;
    int population, dangerousLevel;
    double distance;

    cout << "\n" << endl;
    cout << "----------------------------------------" << endl;
    cout << "                 MENU-1                 " << endl;
    cout << "----------------------------------------" << endl;

    cout << "Enter State Name: ";
    cin.ignore();
    getline(cin, state);
    cout << "Enter City ID: "; cin >> cityId;
    cout << "Enter City Name: "; cin.ignore(); getline(cin, cityName);
    cout << "Enter Population: "; cin >> population;
    cout << "Enter Monitoring Station Name: "; cin.ignore(); getline(cin, stationName);
    cout << "Enter Distance from State HQ (km): "; cin >> distance;
    cout << "Enter Pollutant Name: "; cin.ignore(); getline(cin, pollutantName);
    cout << "Enter Dangerous Level: "; cin >> dangerousLevel;
    cout << "Enter Alert Message: "; cin.ignore(); getline(cin, alertMessage);
    PollutionData newCity(cityId, cityName, population, stationName, distance, pollutantName, dangerousLevel , alertMessage);
    stateCityData[state].push_back(newCity);
    cout << "City added successfully to " << state << ".\n";
}

void checkPollutionThreshold(const string &state) {
    if (stateCityData.find(state) == stateCityData.end()) {
        cout << "No data available for the state: " << state << "\n";
        return;
    }

    cout << "\n==================== Pollution Levels for State: " << state << " ====================\n";
    cout << "+---------+--------------------+------------+-------------------------+-----------------+----------------+-----------------+------------------+\n";
    cout << "| City ID | City Name          | Population | Monitoring Station      |  Distance       | Pollutant Name | Dangerous Level | Alert Message    |\n";
    cout << "+---------+--------------------+------------+-------------------------+-----------------+----------------+-----------------+------------------+\n";

    bool found = false;
    for (const auto &city : stateCityData[state]) {
        if (city.dangerousLevel > 100) { // Assuming 100 is the predefined threshold
            cout << "| " << setw(7) << city.cityId << " | "
                 << setw(18) << left << city.cityName << " | "
                 << setw(10) << right << city.population << " | "
                 << setw(26) << left << city.monitoringStationName << " | "
                 << setw(9) << right << fixed << setprecision(2) << city.distanceFromState << " km | "
                 << setw(14) << left << city.pollutantName << " | "
                 << setw(15) << right << city.dangerousLevel << " | "
                 << setw(16) << left << city.alertMessage << " |\n";
            found = true;
        }
    }

    if (!found) {
        cout << "|                          No cities exceed the threshold of 100.                              |\n";
    }

    cout << "+---------+--------------------+------------+-------------------------+----------------+----------------+-----------------+------------------+\n";
}
//

//==========================

void userDefinedThresholdDetection(const string &state) {
    if (stateCityData.find(state) == stateCityData.end()) {
        cout << "No data available for the state: " << state << "\n";
        return;
    }

    int userThreshold;
    cout << "Enter the dangerous level threshold: ";
    cin >> userThreshold;

    cout << "\n==================== Cities Exceeding Threshold in State: " << state << " ====================\n";
    cout << "+---------+--------------------+------------+-------------------------------+-----------+----------------+-----------------+------------------+\n";
    cout << "| City ID | City Name          | Population | Monitoring Station            | Distance  | Pollutant Name | Dangerous Level | Alert Message    |\n";
    cout << "+---------+--------------------+------------+-------------------------------+-----------+----------------+-----------------+------------------+\n";

    bool found = false;
    for (const auto &city : stateCityData[state]) {
        if (city.dangerousLevel > userThreshold) {
            cout << "| " << setw(7) << city.cityId << " | "
                 << setw(18) << left << city.cityName << " | "
                 << setw(10) << right << city.population << " | "
                 << setw(26) << left << city.monitoringStationName << " | "
                 << setw(9) << right << fixed << setprecision(2) << city.distanceFromState << " km | "
                 << setw(14) << left << city.pollutantName << " | "
                 << setw(15) << right << city.dangerousLevel << " | "
                 << setw(16) << left << city.alertMessage << " |\n";
            found = true;
        }
    }

    if (!found) {
        cout << "|                          No cities exceed the dangerous level threshold.                     |\n";
    }

    cout << "+---------+--------------------+------------+--------------------------------+-----------+----------------+-----------------+------------------+\n";
}

void displayCityData(const string &state) {
    if (stateCityData.find(state) == stateCityData.end()) {
        cout << "No data available for the state: " << state << "\n";
        return;
    }

    cout << "\n================== City Data for " << state << " ==================\n";
    cout << "+---------+------------+------------+----------------------+------------+-------------------+------------------+-------------------+\n";
    cout << "| City ID | City Name  | Population | Monitoring Station   | Distance   | Pollutant Name    | Dangerous Level  | Alert Message     |\n";
    cout << "+---------+ ------------+------------+----------------------+------------+-------------------+------------------+-------------------+\n";

    for (const auto &city : stateCityData[state]) {
        cout << "| " << setw(7) << city.cityId << " | "
             << setw(10) << city.cityName << " | "
             << setw(10) << city.population << " | "
             << setw(20) << city.monitoringStationName << " | "
             << setw(10) << fixed << setprecision(2) << city.distanceFromState << " km | "
             << setw(15) << city.pollutantName << " | "
             << setw(16) << city.dangerousLevel << " | "
             << setw(17) << city.alertMessage << " |\n";
    }

    cout << "+---------+------------+------------+----------------------+------------+-------------------+------------------+-------------------+\n";
}

void listStates() {
    if (stateCityData.empty()) {
        cout << "No states available.\n";
        return;
    }
    unordered_map<int, string> mp;

    cout << "\n" << endl;
    cout << "----------------------------------------" << endl;
    cout << "                 MENU-2                 " << endl;
    cout << "----------------------------------------" << endl;

    cout << "\nAvailable States:\n";
    int index = 0;
    for (const auto &entry : stateCityData) {
        cout << index << ". " << entry.first << "\n";
        mp[index] = entry.first;
        index++;
    }
    viewStateData(mp);
}

void viewStateData(unordered_map<int, string> mp) {
    cout << "\n" << endl;
    cout << "----------------------------------------" << endl;
    cout << "                 MENU-3                 " << endl;
    cout << "----------------------------------------" << endl;

    cout << "1. View City Data for State" << endl;
    cout << "2. Check Pollution Thresholds" << endl;
    cout << "3. User Defined Threshold Detection" << endl;
    cout << "4. Return to main menu" << endl;
    cout << "\n" << endl;
    int n;
    cin >> n;
    switch (n) {
        case 1: {
            cout << "Enter State Number to view city data" << endl;
            int x;
            cin >> x;
            if (mp.find(x) == mp.end()) {
                cout << "Invalid state number. Please try again." << endl;
                return;
            }
            cout << "The selected State is: " << mp[x] << endl;
            int y;
            cout << "\n" << endl;
            cout << "----------------------------------------" << endl;
            cout << "                 MENU-4                 " << endl;
            cout << "----------------------------------------" << endl;
            cout << "1. View Most Polluted City" << endl;
            cout << "2. View Least Polluted City" << endl;
            cout << "3. View all city data" << endl;
            cout << "4. Return back" << endl;
            cin >> y;
            switch (y) {
                case 1: cout << "The most polluted city is " << findCityWithMaxPollution(mp[x]) << endl; break;
                case 2: cout << "The least polluted city is " << findMinPollutionCity(mp[x]) << endl; break;
                case 3: displayCityData(mp[x]); break;
                case 4: return; break;
                default: cout << "Invalid choice. Please try again." << endl; break;
            }
        }
        break;
        case 2: {
            cout << "Enter State Number to check pollution thresholds" << endl;
            int x;
            cin >> x;
            if (mp.find(x) == mp.end()) {
                cout << "Invalid state number. Please try again." << endl;
                return;
            }
            checkPollutionThreshold(mp[x]);
            break;
        }
        case 3: {
            cout << "Enter State Number for user-defined threshold detection" << endl;
            int x;
            cin >> x;
            if (mp.find(x) == mp.end()) {
                cout << "Invalid state number. Please try again." << endl;
                return;
            }
            userDefinedThresholdDetection(mp[x]);
            break;
        }
        case 4: return; break;
        default: cout << "Invalid choice. Please try again." << endl; break;
    }
}

string findCityWithMaxPollution(const string &state) {
    if (stateCityData.find(state) == stateCityData.end()) return "No data available.";
    const auto &cities = stateCityData[state];
    auto maxCity = max_element(cities.begin(), cities.end(), [](const PollutionData &a, const PollutionData &b) {
        return a.dangerousLevel < b.dangerousLevel;
    });
    return maxCity->cityName + " with a dangerous level of " + to_string(maxCity->dangerousLevel);
}

string findMinPollutionCity(const string &state) {
    if (stateCityData.find(state) == stateCityData.end()) return "No data available.";
    const auto &cities = stateCityData[state];
    auto minCity = min_element(cities.begin(), cities.end(), [](const PollutionData &a, const PollutionData &b) {
        return a.dangerousLevel < b.dangerousLevel;
    });
    return minCity->cityName + " with a dangerous level of " + to_string(minCity->dangerousLevel);
}

void saveData(const string &filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Failed to save data to " << filename << "\n";
        return;
    }

    for (const auto &entry : stateCityData) {
        for (const auto &city : entry.second) {
            file << entry.first << "," << city.toCSV() << "\n";
        }
    }

    file.close();
    cout << "Data saved successfully to " << filename << "\n";
}

void loadData(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Failed to load data from " << filename << "\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string state;
        getline(ss, state, ',');
        PollutionData city = PollutionData::fromCSV(ss.str());
        stateCityData[state].push_back(city);
    }

    file.close();
    cout << "Data loaded successfully from " << filename << "\n";
}

//==============================


//-----------------------------------------------------
// Function Prototypes
void login();
void mainMenu1();
void soilPollutionMonitoring();
void dataCollectionModule();
void locationMappingModule();
void dataValidationModule();
void soilTypeClassification();
void pollutantDetectionModule();
void pollutionSeverityGrading();
void historicalDataComparison();
void heatmapGeneration();
void remediationSuggestionModule();
void cropSuitabilityPrediction();
void realTimeMonitoring();
void pollutantSpreadPrediction();
void contaminationSourceDetection();
void costEffectiveCleanupOptimization();
void anomalyDetection();
void forecastFuturePollutionLevels();
void userAuthenticationModule();
void dataStorageModule();
void alertSystem();


//---------------------------------------------------------

void landPollution();
struct WasteSegregation {
    vector<string> wetWaste;
    vector<string> dryWaste;
    vector<string> recyclableWaste;
    vector<string> hazardousWaste;
};

//==================================================================
void fill_weight(vector<vector<int>> &vectors)
{
 srand(static_cast<unsigned>(time(0)));

    // Create 28 vectors and initialize them with random values
    vectors.resize(35);

    for (int i = 0; i < 35; ++i) {
        for (int j = 0; j < 15; ++j) {
            vectors[i].push_back(500 + rand() % (4000 - 500 + 1)); // Generate random values in range 500 to 4000
        }
    }
        cout << endl;
}
//==================================================================
// Function to categorize garbage into paper and plastic
vector<pair<vector<int>, vector<int>>> reicycleGarbageIntoItems(const vector<vector<int>>& garbage) {
    vector<pair<vector<int>, vector<int>>> recycledItems;

    // Process each state's garbage data
    for (const auto& state : garbage) {
        vector<int> paper, plastic;

        for (int value : state) {
            if (value < 1000) {
                paper.push_back(value); // Values below 500 are considered paper
            } else {
                plastic.push_back(value); // Values above or equal to 500 are considered plastic
            }
        }

        // Add paper and plastic data for each state
        recycledItems.push_back({paper, plastic});
    }

    return recycledItems;
}
//04-01-25
void viewWastedisposal(){
    cout<<"Types Of Waste"<<endl;
    cout << "Dry Waste:\n";
    cout << "Refers to all items that are not considered wet/soiled items. "
         << "This includes both recyclable and non-recyclable materials. "
         << "Dry waste includes items such as bottles, cans, clothing, plastic, wood, glass, metals, and paper.\n\n";

    cout << "Wet Waste:\n";
    cout << "Refers to all items that are organic like food items, soiled food wrappers, hygiene products, "
         << "yard waste, tissues and paper towels, as well as any other soiled item that would contaminate the recyclables.\n\n";

    cout << "Sanitary Waste:\n";
    cout << "Refers to all liquid or solid waste originating solely from humans and human activities. "
         << "(Can also include items from medical waste)\n\n";

    cout << "Hazardous Household Waste:\n";
    cout << "Refers to all household products that contain corrosive, toxic, ignitable, or reactive ingredients, other than used oil.\n\n";

    cout << "E-Waste:\n";
    cout << "Refers to all kinds of electronic waste.\n\n";

    cout << "Hazardous Waste:\n";
    cout << "Refers to all items, products and by-products that contain corrosive, toxic, ignitable or reactive ingredients.\n\n";

    cout << "Inert Waste:\n";
    cout << "Refers to waste items that are neither chemically nor biologically reactive nor decompose easily.\n";
    cout<<"------------------------------------------------------------------------------"<<endl;
    cout<<"Colour Code for Bins";
     cout << left << setw(20) << "Type of Waste" << setw(15) << "Color of Bin" << endl;
    cout << string(35, '-') << endl; // Separator line

    // Table Content
    cout << left << setw(20) << "Wet Waste" << setw(15) << "Green" << endl;
    cout << left << setw(20) << "Dry Waste" << setw(15) << "Blue" << endl;
    cout << left << setw(20) << "Sanitary Waste" << setw(15) << "Red" << endl;
    cout << left << setw(20) << "E-Waste" << setw(15) << "Black or Grey" << endl;
    cout << left << setw(20) << "Hazardous Waste" << setw(15) << "Black" << endl;

    // Best Practices for Waste Reduction
    cout << "Best Practices for Waste Reduction\n";
    cout << "-----------------------------------\n";
    cout << "1. Avoid Single-Use Plastics:\n";
    cout << "   - Use cloth bags, metal straws, and reusable bottles.\n\n";
    
    cout << "2. Donate or Reuse:\n";
    cout << "   - Donate old clothes, furniture, or electronics instead of throwing them away.\n\n";
    
    cout << "3. Buy Responsibly:\n";
    cout << "   - Choose products with minimal packaging or recyclable materials.\n\n";
    
    cout << "4. Repair, Don't Replace:\n";
    cout << "   - Repair items like shoes, electronics, or clothing to extend their life.\n\n";
    
    // Community Waste Management
    cout << "Community Waste Management\n";
    cout << "---------------------------\n";
    cout << "1. Participate in Recycling Drives:\n";
    cout << "   - Join or organize community clean-up and recycling initiatives.\n\n";
    
    cout << "2. Collaborate with Local Authorities:\n";
    cout << "   - Report illegal dumping and encourage local bodies to provide waste segregation services.\n\n";
    
    cout << "3. Educate the Community:\n";
    cout << "   - Conduct awareness campaigns about the importance of waste segregation and management.\n\n";
    
    // Benefits of Proper Waste Management
    cout << "Benefits of Proper Waste Management\n";
    cout << "------------------------------------\n";
    cout << "1. Environmental Protection:\n";
    cout << "   - Reduces pollution and conserves natural resources.\n\n";
    
    cout << "2. Economic Benefits:\n";
    cout << "   - Saves money through recycling and reusing materials.\n\n";
    
    cout << "3. Health and Safety:\n";
    cout << "   - Minimizes risks from hazardous waste and improves community hygiene.\n";
    cout<<endl;


}
void displayGarbageTable(){
    cout << left << setw(10) << "Day" 
         << setw(15) << "Garbage Type" << endl;
    cout << string(25, '-') << endl;

    // Print the table rows
    cout << left << setw(10) << "Monday" 
         << setw(15) << "Dry Waste" << endl;
    cout << left << setw(10) << "Tuesday" 
         << setw(15) << "Wet Waste" << endl;
    cout << left << setw(10) << "Wednesday" 
         << setw(15) << "Sanitary Waste" << endl;
    cout << left << setw(10) << "Thursday" 
         << setw(15) << "E-Waste" << endl;
    cout << left << setw(10) << "Friday" 
         << setw(15) << "Hazardous Waste" << endl;
    cout << left << setw(10) << "Saturday" 
         << setw(15) << "Dry Waste" << endl;
    cout << left << setw(10) << "Sunday" 
         << setw(15) << "Wet Waste" << endl;

}
void report(){
    cout<<"Enter the address of dumping site:";
    string s;
    cin>>s;
    cout<<"Thank you. Our team will take action soon"<<endl;
}
void classifyWaste() {
    string item;
    cout << "Enter a waste item: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, item);

    // Convert the input item to lowercase for case-insensitive comparison
    string lower_item = item;
    transform(lower_item.begin(), lower_item.end(), lower_item.begin(), ::tolower);

    // Define waste categories
    vector<string> wetWaste = {"banana peel", "orange peel", "apple core", "vegetable scraps", "coffee grounds", "food waste"};
    vector<string> dryWaste = {"plastic", "paper", "cardboard", "metal", "bottle", "can", "glass"};
    vector<string> hazardousWaste = {"batteries", "light bulbs", "paint", "chemicals", "pesticides"};
    vector<string> electronicWaste = {"laptop", "mobile", "phone", "charger", "tv", "electronic device"};

    // Check for categories and print the result
    for (const auto& waste : wetWaste) {
        if (lower_item == waste) {
            cout << "The item '" << item << "' is categorized as: Wet Waste" << endl;
            return;
        }
    }

    for (const auto& waste : dryWaste) {
        if (lower_item == waste) {
            cout << "The item '" << item << "' is categorized as: Dry Waste" << endl;
            return;
        }
    }

    for (const auto& waste : hazardousWaste) {
        if (lower_item == waste) {
            cout << "The item '" << item << "' is categorized as: Hazardous Waste" << endl;
            return;
        }
    }

    for (const auto& waste : electronicWaste) {
        if (lower_item == waste) {
            cout << "The item '" << item << "' is categorized as: Electronic Waste" << endl;
            return;
        }
    }

    // If no match found
    cout << "The item '" << item << "' is categorized as: Unknown Waste" << endl;
}

// Function to display state data and calculate garbage weight
void displayStategarData(const string& stateName) {
      ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    getline(file, line);  // Skip header

    cout << left << setw(15) << "State" << setw(10) << "CityID" << setw(20) << "CityName"
         << setw(12) << "Population" << setw(15) << "GarbageWeight (Tons)" << endl;
    cout << "---------------------------------------------------------------" << endl;

    while (getline(file, line)) {
        // Skip blank lines
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string state, cityID, cityName, populationStr;

        getline(ss, state, ',');
        getline(ss, cityID, ',');
        getline(ss, cityName, ',');
        getline(ss, populationStr, ',');

        int population = stoi(populationStr);
        double garbageWeight = (population * 3.0) / 1000;

        if (state == stateName) {
            cout << left << setw(15) << state << setw(10) << cityID << setw(20) << cityName
                 << setw(12) << population << setw(15) << fixed << setprecision(2) << garbageWeight << endl;
        }
    }

    file.close();
}
void calculateAverageWeight(const string& stateName) {
    
    ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    getline(file, line);  // Skip header

    double totalWeight = 0.0;
    int cityCount = 0;

    while (getline(file, line)) {
        // Skip blank lines
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string state, cityID, cityName, populationStr;

        getline(ss, state, ',');
        getline(ss, cityID, ',');
        getline(ss, cityName, ',');
        getline(ss, populationStr, ',');

       

        int population = stoi(populationStr);
        double garbageWeight = (population * 3.0) / 1000;  // Convert to tons

        if (state == stateName) {
            totalWeight += garbageWeight;
            cityCount++;
        }
    }

    file.close();

    // Calculate and display the average
    if (cityCount > 0) {
        double averageWeight = totalWeight / cityCount;
        cout << "The average garbage weight for " << stateName << " is "
             << fixed << setprecision(2) << averageWeight << " tons." << endl;
    } else {
        cout << "No cities found for the state: " << stateName << endl;
    }
}
void calculateTotalGarbageWeight(const string& stateName) {
    ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    getline(file, line);  // Skip header

    double totalWeight = 0.0;
    int cityCount = 0;

    while (getline(file, line)) {
        // Skip blank lines
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string state, cityID, cityName, populationStr;

        getline(ss, state, ',');
        getline(ss, cityID, ',');
        getline(ss, cityName, ',');
        getline(ss, populationStr, ',');

        

        int population = stoi(populationStr);
        double garbageWeight = (population * 3.0) / 1000;  // Convert to tons

        if (state == stateName) {
            totalWeight += garbageWeight;
            cityCount++;
        }
    }

    file.close();

    // Display the total garbage weight
    if (cityCount > 0) {
        cout << "The total garbage weight for " << stateName << " is "
             << fixed << setprecision(2) << totalWeight << " tons." << endl;
    } else {
        cout << "No cities found for the state: " << stateName << endl;
    }
}

void findMostAndLeastGarbageProducingStates() {
    ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    getline(file, line);  // Skip header

    // Map to store total garbage weight for each state
    map<string, double> stateGarbageWeights;

    while (getline(file, line)) {
        // Skip blank lines
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string state, cityID, cityName, populationStr;

        getline(ss, state, ',');
        getline(ss, cityID, ',');
        getline(ss, cityName, ',');
        getline(ss, populationStr, ',');


        int population = stoi(populationStr);
        double garbageWeight = (population * 3.0) / 1000;  // Convert to tons

        // Add garbage weight to the respective state's total
        stateGarbageWeights[state] += garbageWeight;
    }

    file.close();

    // Find the most and least garbage-producing states
    string mostGarbageState, leastGarbageState;
    double mostGarbageWeight = numeric_limits<double>::lowest();
    double leastGarbageWeight = numeric_limits<double>::max();

    for (const auto& pair : stateGarbageWeights) {
        if (pair.second > mostGarbageWeight) {
            mostGarbageWeight = pair.second;
            mostGarbageState = pair.first;
        }
        if (pair.second < leastGarbageWeight) {
            leastGarbageWeight = pair.second;
            leastGarbageState = pair.first;
        }
    }

    // Display the results
    if (!stateGarbageWeights.empty()) {
        cout << "The most garbage-producing state is " << mostGarbageState
             << " with " << fixed << setprecision(2) << mostGarbageWeight << " tons." << endl;
        cout << "The least garbage-producing state is " << leastGarbageState
             << " with " << fixed << setprecision(2) << leastGarbageWeight << " tons." << endl;
    } else {
        cout << "No data available to calculate garbage weights." << endl;
    }
}
// Function to calculate and display manure production
void calculateManureProduction() {
    double biodegradableFactor, manureConversionEfficiency;

    cout << "Enter the biodegradable fraction of garbage (e.g., 0.6 for 60%): ";
    cin >> biodegradableFactor;

    cout << "Enter the manure conversion efficiency (e.g., 0.4 for 40%): ";
    cin >> manureConversionEfficiency;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    getline(file, line); // Skip header

    // Prompt user for choice: State or City
    cout << "Do you want to view manure production for:\n";
    cout << "1. An entire state\n";
    cout << "2. A single city\n";
    cout << "Enter your choice (1 or 2): ";
    int choice;
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    if (choice == 1) {
        // State-level calculation
        cout << "Enter the state name: ";
        string stateName;
        getline(cin, stateName);
        double totalGarbageWeight = 0.0;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string state, cityID, cityName, populationStr;

            getline(ss, state, ',');
            getline(ss, cityID, ',');
            getline(ss, cityName, ',');
            getline(ss, populationStr, ',');

            if (!all_of(populationStr.begin(), populationStr.end(), ::isdigit)) {
                continue; // Skip invalid entries
            }

            int population = stoi(populationStr);
            double garbageWeight = (population * 3.0) / 1000; // Convert garbage weight to tons

            if (state == stateName) {
                totalGarbageWeight += garbageWeight;
            }
        }

        if (totalGarbageWeight > 0) {
            double biodegradableWaste = totalGarbageWeight * biodegradableFactor;
            double manureProduction = biodegradableWaste * manureConversionEfficiency;

            cout << "The total garbage weight for " << stateName << " is "
                 << fixed << setprecision(2) << totalGarbageWeight << " tons." << endl;
            cout << "Estimated manure production for " << stateName << " is "
                 << fixed << setprecision(2) << manureProduction << " tons." << endl;
        } else {
            cout << "No data available for the state: " << stateName << endl;
        }
    } else if (choice == 2) {
        // City-level calculation
        cout << "Enter the city name: ";
        string cityName;
        getline(cin, cityName);
        double garbageWeight = 0.0;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string state, cityID, cityNameInFile, populationStr;

            getline(ss, state, ',');
            getline(ss, cityID, ',');
            getline(ss, cityNameInFile, ',');
            getline(ss, populationStr, ',');

            if (!all_of(populationStr.begin(), populationStr.end(), ::isdigit)) {
                continue; // Skip invalid entries
            }

            if (cityNameInFile == cityName) {
                int population = stoi(populationStr);
                garbageWeight = (population * 3.0) / 1000; // Convert garbage weight to tons
                break;
            }
        }

        if (garbageWeight > 0) {
            double biodegradableWaste = garbageWeight * biodegradableFactor;
            double manureProduction = biodegradableWaste * manureConversionEfficiency;

            cout << "The garbage weight for " << cityName << " is "
                 << fixed << setprecision(2) << garbageWeight << " tons." << endl;
            cout << "Estimated manure production for " << cityName << " is "
                 << fixed << setprecision(2) << manureProduction << " tons." << endl;
        } else {
            cout << "No data available for the city: " << cityName << endl;
        }
    } else {
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }

    file.close();
}
// Function to calculate remaining time for landfills to become full
void calculateLandfillTime() {
    ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Map to store state areas and total garbage weights
    map<string, double> stateAreas;
    map<string, double> totalGarbageWeights;

    // User input for state areas
    int numStates;
    cout << "Enter the number of states: ";
    cin >> numStates;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    for (int i = 0; i < numStates; ++i) {
        string stateName;
        double stateArea;

        cout << "Enter the name of state " << (i + 1) << ": ";
        getline(cin, stateName);

        cout << "Enter the area of " << stateName << " (in km^2): ";
        cin >> stateArea;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        stateAreas[(stateName)] = stateArea;
    }

    getline(file, line); // Skip header

    // Read file and calculate total garbage weight per state
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string state, cityID, cityName, populationStr;

        getline(ss, state, ',');
        getline(ss, cityID, ',');
        getline(ss, cityName, ',');
        getline(ss, populationStr, ',');

        if (!all_of(populationStr.begin(), populationStr.end(), ::isdigit)) {
            continue; // Skip invalid entries
        }

        int population = stoi(populationStr);
        double garbageWeight = (population * 3.0) / 1000; // Convert garbage weight to tons

        totalGarbageWeights[state] += garbageWeight;
    }

    file.close();

    // Display results in table format
    cout << setw(20) << left << "State"
         << setw(15) << "Area (km^2)"
         << setw(20) << "Landfill Capacity (tons)"
         << setw(25) << "Garbage Dumped Annually (tons)"
         << setw(20) << "Remaining Years" << endl;

    cout << string(100, '-') << endl;

    for (const auto& state : stateAreas) {
        string stateName = state.first;
        double stateArea = state.second;

        double landfillCapacity = stateArea * 100; // Capacity in tons
        double garbageDumped = totalGarbageWeights[stateName] * 0.4; // 40% of garbage dumped into landfill

        if (garbageDumped > 0) {
            double remainingYears = landfillCapacity / garbageDumped;

            cout << setw(20) << left << stateName
                 << setw(15) << fixed << setprecision(2) << stateArea
                 << setw(20) << fixed << setprecision(2) << landfillCapacity
                 << setw(25) << fixed << setprecision(2) << garbageDumped
                 << setw(20) << fixed << setprecision(2) << remainingYears << endl;
        } else {
            cout << setw(20) << left << stateName
                 << setw(15) << fixed << setprecision(2) << stateArea
                 << setw(20) << "N/A"
                 << setw(25) << "N/A"
                 << setw(20) << "N/A" << endl;
        }
    }
}
void calculateRecyclingPotential() {
    ifstream file("D:\\DAA Airawar Project\\pollution.txt");
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Inputs from the user
    double recyclablePercentage, valuePerTon;
    cout << "Enter the percentage of garbage that can be recycled (e.g., 30 for 30%): ";
    cin >> recyclablePercentage;
    cout << "Enter the economic value of recyclable material per ton (e.g., 50 for $50/ton): ";
    cin >> valuePerTon;

    recyclablePercentage /= 100.0; // Convert to decimal

    map<string, double> totalGarbageWeights;

    getline(file, line); // Skip header

    // Read file and calculate total garbage weight per state
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string state, cityID, cityName, populationStr;

        getline(ss, state, ',');
        getline(ss, cityID, ',');
        getline(ss, cityName, ',');
        getline(ss, populationStr, ',');

        if (!all_of(populationStr.begin(), populationStr.end(), ::isdigit)) {
            continue; // Skip invalid entries
        }

        int population = stoi(populationStr);
        double garbageWeight = (population * 3.0) / 1000; // Convert garbage weight to tons

        totalGarbageWeights[state] += garbageWeight;
    }

    file.close();

    // Display results in table format
    cout << setw(20) << left << "State"
         << setw(20) << "Total Garbage (tons)"
         << setw(20) << "Recyclable (tons)"
         << setw(20) << "Economic Value ($)" << endl;

    cout << string(80, '-') << endl;

    for (const auto& entry : totalGarbageWeights) {
        string stateName = entry.first;
        double totalGarbage = entry.second;
        double recyclableGarbage = totalGarbage * recyclablePercentage;
        double economicValue = recyclableGarbage * valuePerTon;

        cout << setw(20) << left << stateName
             << setw(20) << fixed << setprecision(2) << totalGarbage
             << setw(20) << fixed << setprecision(2) << recyclableGarbage
             << setw(20) << fixed << setprecision(2) << economicValue << endl;
    }
}
// Function to generate random numbers within a range
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to display the infrastructure of a state
void displayStateInfrastructure() {
    string stateName;
    
    // Ask user to enter state name
    cout << "Enter State Name: ";
    getline(cin, stateName);

    // Generate random values for the infrastructure
    int mechanicalSweepers = generateRandomNumber(20, 150); // Range: 20 to 150
    int compactors = generateRandomNumber(30, 200);         // Range: 30 to 200
    int bioMethanePlants = generateRandomNumber(10, 50);    // Range: 10 to 50
    int workers = generateRandomNumber(100, 5000);          // Range: 100 to 5000

    // Display the infrastructure details for the given state
    cout << "Infrastructure of " << stateName << ":\n";
    cout << "Mechanical Sweepers: " << mechanicalSweepers << endl;
    cout << "Compactors: " << compactors << endl;
    cout << "Bio Methane Plants: " << bioMethanePlants << endl;
    cout << "Workers: " << workers << endl;
}
void openWasteCorporationWebsite() {
    string stateName;
    
    // Ask user to enter the state name
    cout << "Enter State Name to visit the Waste Corporation Website: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, stateName);

    // Map of state names to their respective waste management corporation websites
    map<string, string> stateWebsites = {
        {"Goa", "https://gwmc.goa.gov.in/"},
        {"Maharashtra", "https://mpcb.gov.in/wastes-management/municipal-solid-waste"},
        {"Karnataka", "https://site.bbmp.gov.in/departmentwebsites/swm/"},
        {"Uttar Pradesh", "http://www.up.gov.in/"}
        // Add more states and websites as necessary
    };

    // Check if the state exists in the map
    if (stateWebsites.find(stateName) != stateWebsites.end()) {
        string url = stateWebsites[stateName];
        cout << "Opening " << stateName << " Waste Corporation Website: " << url << endl;
        
        // Use system function to open the website in the default browser
        string command = "start " + url; // For Windows (use "open" for macOS)
        system(command.c_str());
    } else {
        cout << "Website not available for " << stateName << ". Please check the state name and try again.\n";
    }
}
void inputPassword(string &password) {
    char ch;
    password = "";

    while(true) {
        ch = getch(); // get character without echoing it to the screen
        if(ch == 13) { // If Enter is pressed
            break;
        } else if(ch == 8) { // If Backspace is pressed
            if(password.length() > 0) {
                password.pop_back();  // Remove last character from password
                cout << "\b \b";      // Move cursor back, overwrite with space, then move cursor back again
            }
        } else {
            password.push_back(ch);  // Add character to password
            cout << "*";  // Display '*' for the entered character
        }
    }
    cout << endl;  // New line after password input is complete
}

//---------------------------------------------------------

int main() {
    login();
    return 0;
}

// Function Definitions

void login() {
    // ANSI escape codes for the colors
    const string boldRed = "\033[1;31m";   // Bold Red
    const string boldBlue = "\033[1;34m";  // Bold Blue
    const string boldPink = "\033[1;35m";  // Bold Magenta (Pink-like)
    const string reset = "\033[0m";        // Reset formatting

    // Bold Red for the header
    cout << boldRed << "============================================================\n";
    cout << "              POLLUTION MONITORING SYSTEM                   \n";
    cout << "============================================================\n" << reset;

    string username, password;
    const string correctUsername = "TEAM-05"; // Replace with the desired username
    const string correctPassword = "DAA";

    // Bold Blue for username and password prompts
    cout << boldBlue << "\nENTER THE USERNAME FOR POLLUTION MONITORING SYSTEM: " << reset;
    cin >> username;

    if (username == correctUsername) {
        while (true) {
            password.clear();
            char ch;

            cout << boldBlue << "ENTER THE PASSWORD FOR POLLUTION MONITORING SYSTEM: " << reset;
            while (true) {
                ch = getch(); // Get a single character without echoing to the console

                if (ch == '\r') { // Enter key is pressed
                    cout << endl;
                    break;
                } else if (ch == '\b') { // Backspace is pressed
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b"; // Move the cursor back, overwrite with a space, then move back again
                    }
                } else {
                    password += ch;
                    cout << '*'; // Display an asterisk for each character
                }
            }

            if (password == correctPassword) {
                // Bold Pink for success message
                cout << boldPink << "\nSuccessfully logged in!" << reset << endl;
                cout << boldPink << "WELL COME TO POLLUTION MONITORING SYSTEM \n " << reset;
                mainMenu1();
                break;
            } else {
                cout << boldBlue << "Incorrect password. Please re-enter." << reset << endl;
            }
        }
    } else {
        cout << boldBlue << "Invalid username." << reset << endl;
    }
}


void mainMenu1() {
    int choice;
    // ANSI escape codes for different colors
    //const string boldRed = "\033[1;31m";
    const string boldYellow = "\033[1;33m";   // Bold Yellow
    const string boldGold = "\033[1;33m";      // Bold Gold (using Bold Yellow as substitute)
    const string boldOrange = "\033[1;31m";    // Bold Red (as an approximation for Orange)
    const string boldBlue = "\033[1;34m";      // Bold Blue
    const string boldWhite = "\033[1;37m";     // Bold White
    const string boldRed = "\033[1;31m";       // Bold Red
    const string boldPink = "\033[1;35m";
    const string boldGreen = "\033[1;32m";    // Bold Green
    const string boldPurple = "\033[1;35m";   // Bold Purple// Bold Pink (Magenta)
    const string reset = "\033[0m";            // Reset formatting

    while (true) {

    cout << boldRed <<"-------------------\n";
               cout <<"   Main Menu         \n";
               cout <<" -------------------\n" << reset;

        //cout << "\nMain Menu:\n";

        // Printing menu items in the specified colors
        cout << boldYellow << "1. Soil Pollution \n" << reset;
        cout << boldPurple << "2. Land Pollution\n" << reset;
        //cout << boldOrange << "3. Air Pollution\n" << reset;
        cout << boldGreen << "3. Air Pollution\n" << reset;
        cout << boldBlue << "4. Water Pollution\n" << reset;
        cout << boldWhite << "5. Sewage Pollution \n" << reset;
        cout << boldRed << "6. Exit\n" << reset;

        cout << boldPink << "Enter your choice: " << reset;
        cin >> choice;

        switch (choice) {
            case 1:
                soilPollutionMonitoring();
                break;
            case 2:
                landPollution();
                break;
            case 3:
                mainMenu();  // Assuming this calls another menu or function
                break;
            case 4:
                waterPollutionMonitoring();
                break;
            case 5:
                run();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
//----------------------------------------------------------------------------------------
void soilPollutionMonitoring() {
    int choice;
    // ANSI escape codes for different colors
    const string boldRed = "\033[1;31m";    // Bold Red
    const string boldYellow = "\033[1;33m"; // Bold Yellow
    const string boldPink = "\033[1;35m";   // Bold Pink
    const string reset = "\033[0m";         // Reset formatting

    while (true) {
        cout << "\n";

        // Separator lines in Bold Red
        cout << boldRed << string(40, '-') << endl; // Separator line
        cout << "Soil Pollution Monitoring Modules:\n";
        cout << boldRed << string(40, '-') << endl; // Separator line
        cout << reset; // Reset formatting for next output

        cout << "\n";

        // Menu items in Bold Yellow
        cout << boldYellow << "1.  Data Collection Module\n";
        cout << "2.  Location Mapping Module\n";
        cout << "3.  Data Validation Module\n";
        cout << "4.  Soil Type Classification\n";
        cout << "5.  Pollutant Detection Module\n";
        cout << "6.  Pollution Severity Grading\n";
        cout << "7.  Historical Data Comparison\n";
        cout << "8.  Heatmap Generation\n";
        cout << "9.  Remediation Suggestion Module\n";
        cout << "10. Crop Suitability Prediction\n";
        cout << "11. Real-Time Monitoring\n";
        cout << "12. Pollutant Spread Prediction\n";
        cout << "13. Contamination Source Detection\n";
        cout << "14. Cost-Effective Cleanup Optimization\n";
        cout << "15. Anomaly Detection\n";
        cout << "16. Forecast Future Pollution Levels\n";
        cout << "17. User Authentication Module\n";
        cout << "18. Data Storage Module(FROM FILE)\n";
        cout << "19. Alert System\n";

        // Option 20 in Bold Red
        cout << boldRed << "20. Return to Main Menu\n" << reset;

        // Prompt in Bold Pink
        cout << boldPink << "\nEnter your choice: " << reset;
        cout << boldPink << "\n";

        cin >> choice;

        switch (choice) {
            case 1:
                dataCollectionModule();
                break;
            case 2:
                locationMappingModule();
                break;
            case 3:
                dataValidationModule();
                break;
            case 4:
                soilTypeClassification();
                break;
            case 5:
                pollutantDetectionModule();
                break;
            case 6:
                pollutionSeverityGrading();
                break;
            case 7:
                historicalDataComparison();
                break;
            case 8:
                heatmapGeneration();
                break;
            case 9:
                remediationSuggestionModule();
                break;
            case 10:
                cropSuitabilityPrediction();
                break;
            case 11:
                realTimeMonitoring();
                break;
            case 12:
                pollutantSpreadPrediction();
                break;
            case 13:
                contaminationSourceDetection();
                break;
            case 14:
                costEffectiveCleanupOptimization();
                break;
            case 15:
                anomalyDetection();
                break;
            case 16:
                forecastFuturePollutionLevels();
                break;
            case 17:
                userAuthenticationModule();
                break;
            case 18:
                dataStorageModule();
                break;
            case 19:
                alertSystem();
                break;
            case 20:
                return; // Return to main menu
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

//---------------------------------------------------------------------------------------------------


void landPollution() {
    // ANSI escape codes for different colors
    const string boldPink = "\033[1;35m";    // Bold Pink
    const string boldRed = "\033[1;31m";     // Bold Red
    const string reset = "\033[0m";          // Reset formatting
    string password="admin";
    vector<int> capacities = {10, 15, 12};
    int y;

    while (true) {
        cout << "-------------------------------------------------------------" << endl;
        cout << boldPink<<"1. Municipal Login" << endl;
        cout << "2. Citizen" << endl;
        cout << boldRed<<"3. Exit" << endl;
        cout << "--------------------------------------------------------------" << endl;
        cin >> y;

        string s, c, t, p, u;
        int r;

        switch (y) {
            case 1: {
                cout <<boldPink<< "Welcome to Municipal Corporation" << endl;
                cout << "Enter Login ID: ";
                cin >> t;
                cout << "Enter Password: ";
                inputPassword(password);
                cout << "\nLogin Successful\n" << endl;

                while (true) {
                    cout <<boldPink<< "1. View Garbage Data for State" << endl;
                    cout << "2. Calculate the Average of the State" << endl;
                    cout << "3. Find the Total Weight of Waste Produced in State" << endl;
                    cout << "4. Find Maximum and Minimum Garbage Producing States" << endl;
                    cout << "5. Produce Manure" << endl;
                    cout << "6. Landfill Usage Tracker" << endl;
                    cout << "7. Calculate Recycling Potential" << endl;
                    cout << "8. View State Infrastructure"<<endl;
                    cout << "9. Enter State Name to visit the Waste Corporation Website  \n";
                    cout << boldRed<<"10. Return to Main Menu" << endl;
                    cin >> r;
                    switch (r) {
                        case 1:
                            cout << "Enter State Name: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, u);
                            displayStategarData(u);
                            break;
                        case 2:
                            cout << "Enter State Name: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, u);
                            calculateAverageWeight(u);
                            break;
                        case 3:
                            cout << "Enter State Name: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, u);
                            calculateTotalGarbageWeight(u);
                            break;
                        case 4:
                            findMostAndLeastGarbageProducingStates();
                            break;
                        case 5:
                            calculateManureProduction();
                            break;
                        case 6:
                            calculateLandfillTime();
                            break;
                        case 7:
                            calculateRecyclingPotential();
                            break;
                        case 8:
                            displayStateInfrastructure();
                            break;
                        case 9:
                            openWasteCorporationWebsite();
                            break;
                        case 10:
                            goto mainMenu; // Exit to main menu
                        default:
                            cout << "Invalid Option!" << endl;
                    }
                }
            }
            case 2: {
                while (true) {
                    cout << boldPink<<"1. View Waste Disposal Technique" << endl;
                    cout << "2. View Waste Pickup Schedule" << endl;
                    cout << "3. Track Disposal Truck" << endl;
                    cout << "4. Report a Dumping Site" << endl;
                    cout << "5. Check the Category of Waste" << endl;
                    cout << boldRed<<"6. Return to Main Menu" << endl;

                    int a;
                    cin >> a;

                    switch (a) {
                        case 1:
                            viewWastedisposal();
                            break;
                        case 2:
                            displayGarbageTable();
                            break;
                        case 3:
                            cout << "Enter State: ";
                            cin >> s;
                            cout << "Enter City: ";
                            cin >> c;
                            // getDisposalStatus(s, c);
                            break;
                        case 4:
                            report();
                            break;
                        case 5:
                            classifyWaste();
                            break;
                        case 6:
                            goto mainMenu; // Exit to main menu
                        default:
                            cout << "Invalid Option!" << endl;
                    }
                }
            }
            case 3:
                cout << "Exiting Program. Thank you!" << endl;
                return; // Exit the program
            default:
                cout << "Invalid Input! Please try again." << endl;
        }
    mainMenu:
        continue; // Return to the main menu
    }
}

//============================================================================
//AIR POLLUTON

void mainMenu() {
    while (true) {
        cout << "\n================== State Pollution Monitoring System ==================\n";

        cout << "----------------------------------------" << endl;
        cout << "                 MENU-1                 " << endl;
        cout << "----------------------------------------" << endl;

        cout << "1. List States\n";
        cout << "2. Add City Data\n";
        cout << "3. View City Data\n";
        //cout << "4. Calculate Distance Between Cities\n";
        //cout << "5. Save Data\n";
        //cout << "6. Load Data\n";
        cout << "7. Load Cities from File(D:\\DAA Airawar Project\\pollution.txt)\n";
        cout << "8. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listStates();
                break;
            case 2:
                addCityToState();
                break;
            case 3: {
                string state;
                cout << "Enter State Name: ";
                cin.ignore();
                getline(cin, state);
                displayCityData(state);
                break;
            }
            case 4:
                // Call the distance calculation function (not implemented in this snippet)
                break;
            case 5: {
                string filename;
                cout << "Enter filename to save data: ";
                cin >> filename;
                saveData(filename);
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to load data: ";
                cin >> filename;
                loadData(filename);
                break;
            }
            case 7: {
                string filename;
                cout << "Enter full file path to load cities from: ";
                cin.ignore();
                getline(cin, filename);
                readFromFileAndAddCities(filename);
                break;
            }
            case 8:
                cout << "Exiting the system.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}


//=====================================================
//----------------------------------------------------------------------------------------------------
// Placeholder function implementations
//--------------------------------------------------------------------------------------------------------------------

void dataCollectionModule()
{
    cout << "Data Collection Module: Collecting soil parameters (pH, moisture, pollutant levels)..." << endl;

    const int numInputs = 15; // Number of inputs to simulate

    vector<float> pHValues = {6.8, 5.5, 7.2, 6.0, 8.1, 7.0, 5.8, 6.5, 7.5, 6.9, 5.7, 8.3, 6.4, 7.1, 5.9};
    vector<float> moistureValues = {45, 35, 50, 60, 30, 55, 40, 65, 35, 50, 42, 25, 48, 53, 38};
    vector<float> pollutantLevels = {12, 8, 15, 20, 5, 10, 18, 22, 7, 12, 14, 4, 16, 9, 19};

    // Displaying collected data in a table format
    cout << "\nData Collection Completed. Here are the collected parameters:\n";

    cout << "\n";

    cout << string(54, '-') << endl; // Separator line
    cout << left << setw(10) << "Sample"
         << setw(10) << "pH"
         << setw(15) << "Moisture (%)"
         << setw(15) << "Pollutant (mg/kg)" << endl;

    cout << string(54, '-') << endl; // Separator line

    for (int i = 0; i < numInputs; ++i)
    {
        cout << left << setw(10) << (i + 1)

             << setw(10) << pHValues[i]
             << setw(15) << moistureValues[i]
             << setw(15) << pollutantLevels[i] << endl;
    }

        cout << "\n";


    cout << "Press any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();
}

//-----------------------------------------------------------------------------------------------------------

void locationMappingModule()
{
    cout << "\n";

    // Display module start message
    cout << "Location Mapping Module: Pinpointing locations of soil samples..." << endl;

    // Number of inputs (20 real-time locations)
    const int numInputs = 20;

    // Real-time location data from India
    vector<string> locationNames =
    {
        "New Delhi", "Mumbai", "Kolkata", "Chennai", "Bengaluru",
        "Hyderabad", "Ahmedabad", "Pune", "Jaipur", "Lucknow",
        "Kanpur", "Nagpur", "Indore", "Bhopal", "Visakhapatnam",
        "Patna", "Vadodara", "Ghaziabad", "Ludhiana", "Agra"
    };

    vector<float> latitudes =
    {
        28.6139, 19.0760, 22.5726, 13.0827, 12.9716,
        17.3850, 23.0225, 18.5204, 26.9124, 26.8467,
        26.4499, 21.1458, 22.7196, 23.2599, 17.6868,
        25.5941, 22.3072, 28.6692, 30.9010, 27.1767
    };

    vector<float> longitudes =
    {
        77.2090, 72.8777, 88.3639, 80.2707, 77.5946,
        78.4867, 72.5714, 73.8567, 75.7873, 80.9462,
        80.3319, 79.0882, 75.8577, 77.4126, 83.2185,
        85.1376, 73.1812, 77.4538, 75.8573, 78.0081
    };

    // Display the mapping in a table format

    cout << "\nLocation Mapping Completed. Here are the soil sample locations:\n";

    cout << string(65, '-') << endl;

    cout << left << setw(15) << "Sample ID"
         << setw(20) << "Location Name"
         << setw(15) << "Latitude"
         << setw(15) << "Longitude" << endl;

    // Separator line
    cout << string(65, '-') << endl;

    // Loop through each location and display the details
    for (int i = 0; i < numInputs; ++i)
    {
        cout << left << setw(15) << (i + 1)
             << setw(20) << locationNames[i]
             << setw(15) << latitudes[i]
             << setw(15) << longitudes[i] << endl;
    }

    // Prompt user to press any key to return to the main menu
    cout << "\n";

    cout << "Press any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();
}

//-------------------------------------------------------------------------------------------------------------

void dataValidationModule()
{
    // Display module start message
    cout << "\n";

    cout << "Data Validation Module: Validating collected data..." << endl;

    // Sample data for validation (can replace with actual data collected earlier)
    const int numSamples = 10;

    vector<float> pHValues = {6.8, 5.5, 7.2, 6.0, 8.1, 14.5, -1.0, 7.0, 5.8, 6.5};

    vector<float> moistureValues = {45, 35, 50, 60, 105, 30, 55, -5, 65, 35};

    vector<float> pollutantLevels = {12, 8, 15, 2000, 5, 10, 18, 22, -7, 12};


    // Vector to store validation results
    vector<string> validationResults(numSamples);

    // Validation rules
    for (int i = 0; i < numSamples; ++i)
        {

        bool isValid = true;
        string result = "Valid";

        // Validate pH (0-14)
        if (pHValues[i] < 0 || pHValues[i] > 14)
        {
            result = "Invalid pH";
            isValid = false;
        }

        // Validate moisture content (0-100%)
        if (moistureValues[i] < 0 || moistureValues[i] > 100)
        {
            result = isValid ? "Invalid Moisture" : result + ", Moisture";
            isValid = false;
        }

        // Validate pollutant levels (0-1000 mg/kg)
        if (pollutantLevels[i] < 0 || pollutantLevels[i] > 1000)

        {
            result = isValid ? "Invalid Pollutants" : result + ", Pollutants";
            isValid = false;
        }

        // Store the validation result
        validationResults[i] = result;
    }

    // Display validation results in a table format
    cout << "\nValidation Results:\n";
    cout << string(75, '-') << endl;

    cout << left << setw(10) << "Sample"
         << setw(10) << "pH"
         << setw(15) << "Moisture (%)"
         << setw(20) << "Pollutant (mg/kg)"
         << setw(20) << "Validation Result" << endl;

    // Separator line
    cout << string(75, '-') << endl;

    // Loop through each sample and display the details
    for (int i = 0; i < numSamples; ++i)
    {

        cout << left << setw(10) << (i + 1)
             << setw(10) << pHValues[i]
             << setw(15) << moistureValues[i]
             << setw(20) << pollutantLevels[i]
             << setw(20) << validationResults[i] << endl;
    }

    // Prompt user to press any key to return to the main menu
    cout << "\n";

    cout << "Data validation completed. Press any key to return to the main menu." << endl;

    cout << "\n";

    cout << "Press any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}


//----------------------------------------------------------------------------------------------

//Algorithm Used: Rule-Based Classification

void soilTypeClassification() {
    cout << "Soil Type Classification: Classifying soil into types (sandy, clay, loamy)..." << endl;

    // Number of samples
    const int numSamples = 20;

    // Sample data (you can replace this with actual collected data)
    vector<float> pHValues = {6.5, 7.8, 5.5, 7.2, 6.0, 8.1, 7.0, 5.8, 7.5, 6.9,
                              5.2, 7.4, 6.8, 6.3, 5.7, 6.6, 7.3, 6.1, 7.0, 6.2};

    vector<float> moistureValues = {45, 35, 50, 60, 40, 55, 48, 32, 50, 47,
                                    52, 44, 38, 42, 50, 53, 46, 36, 49, 41};

    vector<float> pollutantLevels = {10, 20, 15, 25, 5, 12, 18, 8, 14, 10,
                                     6, 22, 19, 9, 16, 21, 20, 11, 15, 13};

    // Classification results
    vector<string> soilTypes(numSamples);

    for (int i = 0; i < numSamples; ++i) {
        // Classification logic
        if (pHValues[i] >= 6.0 && pHValues[i] <= 7.5 && moistureValues[i] > 40 && pollutantLevels[i] < 20) {
            soilTypes[i] = "Loamy";
        } else if (pHValues[i] < 6.0 && moistureValues[i] <= 40) {
            soilTypes[i] = "Sandy";
        } else if (pHValues[i] > 7.5 || moistureValues[i] > 50) {
            soilTypes[i] = "Clay";
        } else {
            soilTypes[i] = "Liquid Form";
        }
    }

    // Display classification results in a table format
    cout << "\nSoil Classification Results:\n";
    cout << string(70, '-') << endl;

    cout << left << setw(10) << "Sample"
         << setw(10) << "pH"
         << setw(15) << "Moisture (%)"
         << setw(20) << "Pollutant (mg/kg)"
         << setw(15) << "Soil Type" << endl;

    cout << string(70, '-') << endl;

    for (int i = 0; i < numSamples; ++i) {
        cout << left << setw(10) << (i + 1)
             << setw(10) << pHValues[i]
             << setw(15) << moistureValues[i]
             << setw(20) << pollutantLevels[i]
             << setw(15) << soilTypes[i] << endl;
    }

    cout << "\n";

    cout << "Soil classification completed." << endl;
    cout << "Press any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}


//------------------------------------------------------------------------------------------------
//Algorithm Used: Threshold-Based Classification

void pollutantDetectionModule()
{
    cout << "Pollutant Detection Module: Identifying and quantifying pollutants..." << endl;

    // Number of samples
    const int numSamples = 20;

    // Sample pollutants data (you can replace this with actual collected data)
    vector<float> pollutantLevels = {15, 120, 45, 200, 30, 320, 100, 400, 250, 80,
                                     10, 500, 150, 220, 90, 60, 280, 360, 110, 55};

    // Ask user to set pollutant threshold levels
    cout << "\n";

    float lowThreshold, moderateThreshold, highThreshold;

    cout << "Enter the pollutant threshold for 'Safe' (lowThreshold): ";
    cin >> lowThreshold;

    cout << "Enter the pollutant threshold for 'Warning' (moderateThreshold): ";
    cin >> moderateThreshold;

    cout << "Enter the pollutant threshold for 'Hazardous' (highThreshold): ";
    cin >> highThreshold;

    // Classification of pollutant levels
    vector<string> pollutantCategories(numSamples);

    for (int i = 0; i < numSamples; ++i)
    {
        if (pollutantLevels[i] <= lowThreshold)
        {
            pollutantCategories[i] = "Safe";
        }
    else if (pollutantLevels[i] > lowThreshold && pollutantLevels[i] <= moderateThreshold)
        {
            pollutantCategories[i] = "Warning";
        }
    else if (pollutantLevels[i] > moderateThreshold && pollutantLevels[i] <= highThreshold)
        {
            pollutantCategories[i] = "Hazardous";
        }
    else
        {
            pollutantCategories[i] = "Critical";
        }
    }

    // Displaying pollutant levels and classifications in a table format
    cout << "\nPollutant Detection Results:\n";

    cout << string(50, '-') << endl;

    cout << left << setw(10) << "Sample"
         << setw(20) << "Pollutant (mg/kg)"
         << setw(15) << "Category" << endl;

    cout << string(50, '-') << endl;

    for (int i = 0; i < numSamples; ++i)

    {
        cout << left << setw(10) << (i + 1)
             << setw(20) << pollutantLevels[i]
             << setw(15) << pollutantCategories[i] << endl;
    }

    cout << "\n";

    cout << "Pollutant detection completed." << endl;
    cout << "Press any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}


//--------------------------------------------------------------------------------------------
//K-Means Clustering Algorithm:

void pollutionSeverityGrading()
{
    cout << "Pollution Severity Grading: Assigning severity levels to pollution using K-Means Clustering..." << endl;
    cout << "\n." << endl;

    // Number of samples and clusters
    const int numSamples = 20;

    const int numClusters = 3; // Low, Moderate, High (severity levels)

    // Sample pollution data (replace with actual data if available)
    vector<float> pollutantLevels = {15, 120, 45, 200, 30, 320, 100, 400, 250, 80,
                                     10, 500, 150, 220, 90, 60, 280, 360, 110, 55};

    // Initialize centroids (randomly selecting from data points)
    vector<float> centroids(numClusters);
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < numClusters; ++i)
    {
        centroids[i] = pollutantLevels[rand() % numSamples];
    }

    vector<int> clusterAssignments(numSamples); // Cluster assignments for each sample
    vector<float> newCentroids(numClusters);
        // Updated centroids

    bool centroidsChanged = true;
    int iterations = 0;

    // K-Means Clustering Loop
    while (centroidsChanged && iterations < 100)
    { // Stop after 100 iterations to avoid infinite loop

        centroidsChanged = false;

        // Step 1: Assign each sample to the nearest centroid
        for (int i = 0; i < numSamples; ++i)
        {
            float minDistance = numeric_limits<float>::max();
            int bestCluster = 0;
            for (int j = 0; j < numClusters; ++j)
            {
                float distance = abs(pollutantLevels[i] - centroids[j]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    bestCluster = j;
                }
            }
            clusterAssignments[i] = bestCluster;
        }

        // Step 2: Update centroids by calculating the mean of assigned samples
        vector<float> sum(numClusters, 0.0);
        vector<int> count(numClusters, 0);

        for (int i = 0; i < numSamples; ++i)
        {
            int cluster = clusterAssignments[i];
            sum[cluster] += pollutantLevels[i];
            count[cluster]++;
        }

        for (int j = 0; j < numClusters; ++j)
        {
            if (count[j] > 0)
            {
                newCentroids[j] = sum[j] / count[j];
            }
        else
            {
                newCentroids[j] = centroids[j]; // Keep old centroid if no samples are assigned
            }
        }

        // Check if centroids have changed
        for (int j = 0; j < numClusters; ++j)
        {
            if (abs(newCentroids[j] - centroids[j]) > 1e-4)
            { // Small tolerance for change
                centroidsChanged = true;
                break;
            }
        }

        centroids = newCentroids; // Update centroids
        iterations++;
    }

    // User input for severity level names
    string severity1, severity2, severity3;
    cout << "Enter the name for Severity (e.g., Safe): ";
    cin >> severity1;
    cout << "Enter the name for Severity(e.g., Moderate): ";
    cin >> severity2;
    cout << "Enter the name for Severity (e.g., Severe): ";
    cin >> severity3;

    // Real-time cluster names based on user input
    vector<string> clusterNames = {severity1, severity2, severity3}; // Severity levels from user input

    // Step 3: Output Results
    cout << "\nK-Means Clustering Completed \n";
    cout << "Cluster Centroids:\n";
    for (int i = 0; i < numClusters; ++i)
    {
        cout << clusterNames[i] << ": " << centroids[i] << " mg/kg\n";
    }

    // Displaying the menu options to the user
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. See only " << severity1 << " Samples\n";
        cout << "2. See only " << severity2 << " Samples\n";
        cout << "3. See only " << severity3 << " Samples\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

            case 1:
                cout << "\nDisplaying " << severity1 << " Samples:\n";
                cout << left << setw(10) << "Sample"
                     << setw(20) << "Pollutant (mg/kg)"
                     << setw(15) << "Severity" << endl;
                cout << string(50, '-') << endl;

                for (int i = 0; i < numSamples; ++i)
                {
                    if (clusterAssignments[i] == 0)
                    { // Severity Level 1
                        cout << left << setw(10) << (i + 1)
                             << setw(20) << pollutantLevels[i]
                             << setw(15) << clusterNames[clusterAssignments[i]] << endl;
                    }
                }
                break;

            case 2:
                cout << "\nDisplaying " << severity2 << " Samples:\n";
                cout << left << setw(10) << "Sample"
                     << setw(20) << "Pollutant (mg/kg)"
                     << setw(15) << "Severity" << endl;
                cout << string(50, '-') << endl;
                for (int i = 0; i < numSamples; ++i)
                {
                    if (clusterAssignments[i] == 1)
                    { // Severity Level 2
                        cout << left << setw(10) << (i + 1)
                             << setw(20) << pollutantLevels[i]
                             << setw(15) << clusterNames[clusterAssignments[i]] << endl;
                    }
                }
                break;

            case 3:
                cout << "\nDisplaying " << severity3 << " Samples:\n";
                cout << left << setw(10) << "Sample"
                     << setw(20) << "Pollutant (mg/kg)"
                     << setw(15) << "Severity" << endl;
                cout << string(50, '-') << endl;
                for (int i = 0; i < numSamples; ++i)
                {
                    if (clusterAssignments[i] == 2)
                  { // Severity Level 3
                        cout << left << setw(10) << (i + 1)
                             << setw(20) << pollutantLevels[i]
                             << setw(15) << clusterNames[clusterAssignments[i]] << endl;
                    }
                }
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4); // Loop until the user selects "Exit"

    cout << "\nPollution severity grading completed." << endl;
    cout << " Press any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}

//--------------------------------------------------------------------------------------------



void historicalDataComparison()
{
    cout << "Historical Data Comparison: Comparing current data with historical records..." << endl;

    // Define some sample historical data (pollution levels in mg/kg)
    vector<float> historicalData = {50.0, 75.5, 120.0, 200.5, 90.3, 60.8, 300.0, 180.0, 45.7, 160.3};  // Example historical data

    // Collect current data (pollution levels)
    vector<float> currentData(10);

    cout << "\n" << endl;

    cout << "Please enter current pollution levels (in mg/kg):\n";

    cout << "\n" << endl;

    for (int i = 0; i < 10; ++i)
    {
        while (true)
       {
            cout << "Enter pollution level for sample " << (i + 1) << ": ";
            cin >> currentData[i];

            if (cin.fail() || currentData[i] < 0)
            {
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

                cout << "Invalid input. Pollution level should be a non-negative number.\n";
            }
            else
            {
                break; // Valid input
            }
        }
    }

    // Comparison logic: Compare current data with historical data
    cout << "\nComparison of Current Data with Historical Records:\n";

    cout << string(75, '-') << endl;

    cout << left << setw(15) << "Sample"
         << setw(20) << "Historical Data"
         << setw(20) << "Current Data"
         << setw(20) << "Difference" << endl;

    cout << string(75, '-') << endl;

    for (int i = 0; i < 10; ++i) {
        float difference = currentData[i] - historicalData[i];
        string comparison = (difference > 0) ? "Higher" : (difference < 0) ? "Lower" : "Same";

        cout << left << setw(15) << (i + 1)
             << setw(20) << historicalData[i]
             << setw(20) << currentData[i]
             << setw(20) << comparison << endl;
    }

    cout << "\n" << endl;


    cout << "Historical data comparison completed." << endl;
    cout << "Press any key to return to the main menu." << endl;


    cin.ignore();
    cin.get();
}


//--------------------------------------------------------------------------------------------

void heatmapGeneration()
{
    // ANSI escape codes for colors (based on pollution levels)
    const string RED = "\033[31m";
    const string YELLOW = "\033[33m";
    const string GREEN = "\033[32m";
    const string RESET = "\033[0m";

    // Simple bilinear interpolation function
    auto bilinearInterpolation = [](float x, float y, float Q11, float Q12, float Q21, float Q22) {
        return (1 - x) * (1 - y) * Q11 + x * (1 - y) * Q21 + (1 - x) * y * Q12 + x * y * Q22;
    };

    cout << "Heatmap Generation: Visualizing pollution intensity across a region..." << endl;

    // Define grid size (rows x columns)
    const int rows = 5;
    const int cols = 5;

    // Define pollution data at certain points (known data points)
    vector<vector<float>> pollutionData(rows, vector<float>(cols, -1));  // -1 indicates missing data

    // Populate known data points
    pollutionData[0][0] = 50.0;  // Top-left
    pollutionData[0][4] = 120.0; // Top-right
    pollutionData[4][0] = 80.0;  // Bottom-left
    pollutionData[4][4] = 150.0; // Bottom-right

    // Display the initial input pollution levels (known points)
    cout << "\nInput Pollution Levels (Known Data Points):\n";
    for (int i = 0; i < rows; ++i)
        {
        for (int j = 0; j < cols; ++j)
         {
            if (pollutionData[i][j] == -1)

            {
                cout << setw(6) << "X";  // Mark unknown data with X
            }
    else
        {
                cout << setw(6) << pollutionData[i][j];
            }
        }
        cout << endl;
    }

    // Perform bilinear interpolation to estimate values in the grid
    for (int i = 1; i < rows - 1; ++i)
        {
        for (int j = 1; j < cols - 1; ++j)
         {
            if (pollutionData[i][j] == -1)
             {  // If data is missing
                // Interpolate based on the four nearest known values
                pollutionData[i][j] = bilinearInterpolation(
                    (float)(i) / (rows - 1), (float)(j) / (cols - 1),
                    pollutionData[0][0], pollutionData[0][4],
                    pollutionData[4][0], pollutionData[4][4]
                );
            }
        }
    }

    // Display the grid after interpolation (output)
    cout << "\nGreen: Low pollution levels (values < 60.0):\n";
    cout << "Yellow: Moderate pollution levels (values between 60.0 and 120.0)\n";
    cout << "Red: High pollution levels (values > 120.0)\n";

    cout << "\nOutput Heatmap (Pollution Levels After Interpolation):\n";

    for (int i = 0; i < rows; ++i)
        {
        for (int j = 0; j < cols; ++j)
         {
            float pollutionLevel = pollutionData[i][j];

            // Color coding based on pollution level
            string color;
            if (pollutionLevel < 60)
            {
                color = GREEN;  // Low pollution
            }
            else if (pollutionLevel < 120)
            {
                color = YELLOW; // Moderate pollution
            }
            else
            {
                color = RED;    // High pollution
            }

            // Display the pollution level with color
            cout << color << setw(6) << pollutionLevel << RESET;
        }
        cout << endl;
    }

    cout << "\nHeatmap generation completed. Press any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();
}


//----------------------------------------------------------------------------------------

void remediationSuggestionModule()
{
    cout << "Remediation Suggestion Module: Suggesting ways to clean contaminated soil..." << endl;

    // Example of a simple rule-based logic for soil remediation suggestions:
    // If pollutant level is high, suggest remediation techniques
     cout << "\n" ;

    float pollutantLevel;
    cout << "Enter current pollutant level (mg/kg): ";
    cin >> pollutantLevel;

    cout << "\n" ;

    // Suggest remediation actions based on pollutant levels
    if (pollutantLevel > 500)
    {
        cout << "Pollutant level is hazardous. Suggesting advanced remediation techniques such as bioremediation or phytoremediation." << endl;
    }
    else if (pollutantLevel > 200)
    {
        cout << "Pollutant level is moderate. Suggesting soil washing or air stripping techniques." << endl;
    }
    else if (pollutantLevel > 50)
    {
        cout << "Pollutant level is low. Suggesting natural attenuation or use of soil amendments." << endl;
    }
    else
    {
        cout << "Pollutant level is safe. No remediation necessary." << endl;
    }

    cout << "\n" ;


    cout << "Remediation suggestions completed." << endl;
    cout << "Press any key to return to the main menu." << endl;


    cin.ignore();
    cin.get();
}
//------------------------------------------------------------------------

void cropSuitabilityPrediction()
{
    cout << "Crop Suitability Prediction: Recommending suitable crops based on soil health..." << endl;

    // Example of a simple crop suitability prediction based on soil pH and organic content.
    float soilPH, organicContent;

    cout << "\n" ;

    cout << "Enter soil pH (valid range: 0-14): ";
    cin >> soilPH;
    cout << "Enter organic content (%): ";
    cin >> organicContent;

    // Crop suggestions based on simple rules (for demonstration purposes)
        cout << "\n" ;

    if (soilPH < 5.5)
    {
        cout << "Soil is acidic. Suitable crops: Rice, Tea, Potato." << endl;
    }
    else if (soilPH >= 5.5 && soilPH <= 7.0)
    {
        if (organicContent > 2)
        {
            cout << "Soil is ideal for most crops like Wheat, Corn, Beans." << endl;
        }
    else
        {
            cout << "Soil is suitable for legumes like Peas, Soybeans." << endl;
        }
    }
    else
    {
        cout << "Soil is alkaline. Suitable crops: Barley, Cotton, Alfalfa." << endl;
    }

    cout << "Crop suitability prediction completed." << endl;
    cout << "Press any key to return to the main menu." << endl;


    cin.ignore();
    cin.get();
}


//-----------------------------------------------------------------------------------

void realTimeMonitoring()
{

    cout << "Real-Time Monitoring: Continuously monitoring soil health..." << endl;

    // Use simple moving average for trend analysis (as an example)
    const int windowSize = 5;

    vector<float> moistureLevels(windowSize);
    float newReading;
    float sum = 0;
    float movingAverage;

    cout << "\n" ;

    cout << "Enter 5 soil moisture readings (in percentage):\n";
    for (int i = 0; i < windowSize; ++i)

    {
        cout << "Reading " << i + 1 << ": ";
        cin >> moistureLevels[i];
        sum += moistureLevels[i];
    }

    cout << "\n" ;

    movingAverage = sum / windowSize;
    cout << "Initial moving average of moisture levels: " << movingAverage << "%" << endl;

    // Continuously monitor and calculate moving average (simulating real-time data monitoring)
    char continueMonitoring = 'y';
    while (continueMonitoring == 'y' || continueMonitoring == 'Y')
    {
        cout << "Enter new soil moisture reading: ";
        cin >> newReading;

        // Slide window for moving average calculation
        sum -= moistureLevels[0];  // Remove the oldest reading
        sum += newReading;          // Add the new reading
        movingAverage = sum / windowSize;

        cout << "Updated moving average of moisture levels: " << movingAverage << "%" << endl;

        // Ask the user if they want to continue monitoring
        cout << "Do you want to continue monitoring? (y/n): ";
        cin >> continueMonitoring;
    }


    cout << "Real-time monitoring  completed." << endl;
    cout << "Press any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}


//--------------------------------------------------------------------------------------
void pollutantSpreadPrediction()
{
    cout << "Pollutant Spread Prediction: Predicting how pollutants will spread over time..." << endl;

    // Example: Simple simulation using Cellular Automata for pollutant spread
    const int gridSize = 5; // 5x5 grid
    vector<vector<int>> grid(gridSize, vector<int>(gridSize, 0)); // 0 = no pollution, 1 = polluted

    // Initial polluted areas (arbitrary for demo)
    grid[2][2] = 1; // Start pollution at center

    // Perform 3 rounds of pollution spread
    for (int round = 0; round < 3; ++round)
    {
        vector<vector<int>> nextGrid = grid;
        for (int i = 1; i < gridSize - 1; ++i)
        {
            for (int j = 1; j < gridSize - 1; ++j)
             {
                if (grid[i][j] == 1)
                 {
                    // Spread pollution to neighboring cells
                    nextGrid[i-1][j] = nextGrid[i+1][j] = nextGrid[i][j-1] = nextGrid[i][j+1] = 1;
                }
            }
        }
        grid = nextGrid;  // Update grid to next state



        // Display the grid after each round of pollution spread
        cout << "Round " << round + 1 << " of pollutant spread:" << endl;

        for (int i = 0; i < gridSize; ++i)
            {
            for (int j = 0; j < gridSize; ++j)
            {
                cout << grid[i][j] << " ";  // 1 represents polluted, 0 represents clean
            }
            cout << endl;
        }
    }

    cout << "Pollutant spread prediction completed. \n Press any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();
}

//---------------------------------------------------------------------------------------------


void contaminationSourceDetection()
{
    cout << "Contamination Source Detection: Identifying the probable source of soil pollution..." << endl;

    // Example: Reverse Gradient Tracing (simplified model for demo)
    const int gridSize = 5;
    vector<vector<int>> pollutionLevels(gridSize, vector<int>(gridSize, 0));  // Pollution intensity
    pollutionLevels[2][2] = 100;  // Initial contamination point

    // Trace contamination back through the grid (simplified)
    for (int round = 0; round < 3; ++round)

    {
        vector<vector<int>> nextPollutionLevels = pollutionLevels;
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                if (pollutionLevels[i][j] > 0)
                {
                    // Spread contamination back towards neighbors
                    if (i > 0) nextPollutionLevels[i-1][j] = pollutionLevels[i][j] - 10;
                    if (i < gridSize - 1) nextPollutionLevels[i+1][j] = pollutionLevels[i][j] - 10;
                    if (j > 0) nextPollutionLevels[i][j-1] = pollutionLevels[i][j] - 10;
                    if (j < gridSize - 1) nextPollutionLevels[i][j+1] = pollutionLevels[i][j] - 10;
                }
            }
        }
        pollutionLevels = nextPollutionLevels;  // Update pollution levels

        // Display the pollution levels for each round
        cout<<"\n";

        cout << "Pollution levels after round " << round + 1 << ":" << endl;

        cout<<"\n";

        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                cout << pollutionLevels[i][j] << " ";  // Display contamination levels
            }
            cout << endl;
        }
    }

    cout<<"\n";

    cout << "Contamination source detection completed. \n Press any key to return to the main menu." << endl;

    cin.ignore();

    cin.get();
}

//--------------------------------------------------------------------------------------

void costEffectiveCleanupOptimization()
{
    cout << "Cost-Effective Cleanup Optimization: Calculating the cheapest method to remediate soil..." << endl;

    // Example: Simple linear programming model for cost optimization
    const float costPerUnit = 50.0;  // Cost per unit of soil to clean (in rs)

    // Ask the user for the contaminated area
    float contaminatedArea;
    cout << "Enter the contaminated area (in square meters): ";
    cin >> contaminatedArea;

    // Calculate the total cleanup cost (for demo, we'll assume the method is uniform)
    float cleanupCost = contaminatedArea * costPerUnit;

    // Display the result
    cout << "\nEstimated cleanup cost for " << contaminatedArea << " square meters of contaminated soil: RS " << cleanupCost << endl;

    cout << "\nCleanup optimization completed.\nPress any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}

//--------------------------------------------------------------------------------------

void anomalyDetection()
{
    // Function to print the table
    auto printTable = [](const vector<vector<string>>& tableData, const vector<string>& headers) {
        // Printing headers
        for (const string& header : headers)

        {
            cout << setw(20) << header;
        }

        cout << endl;
        cout << string(100, '-') << endl;  // Table separator

        // Printing data
        for (const auto& row : tableData)
        {

            for (const string& cell : row)
            {
                cout << setw(20) << cell;
            }
            cout << endl;
        }
        cout << endl;
    };

    cout << "Anomaly Detection: Identifying unusual patterns in soil data..." << endl;

    // Sample soil data: {Sample ID, pH, Moisture Content, Pollution Level}
    vector<vector<float>> soilData =
    {
        {1, 6.5, 40.0, 50.0},   // Normal data
        {2, 7.0, 45.0, 120.0},  // Moderate data
        {3, 5.5, 30.0, 200.0},  // Possible anomaly (high pollution)
        {4, 6.2, 35.0, 45.0},   // Normal data
        {5, 8.0, 50.0, 400.0},  // Anomaly (high pollution)
        {6, 6.7, 42.0, 100.0},  // Normal data
        {7, 7.5, 38.0, 250.0}   // Anomaly (high pollution)
    };

    // Thresholds for anomaly detection
    const float PH_THRESHOLD_LOW = 5.0;
    const float PH_THRESHOLD_HIGH = 8.0;
    const float MOISTURE_THRESHOLD_LOW = 30.0;
    const float MOISTURE_THRESHOLD_HIGH = 50.0;
    const float POLLUTION_THRESHOLD = 200.0;  // Flag pollution greater than 200 as an anomaly

    // Store results: {Sample ID, pH, Moisture, Pollution Level, Anomaly Flag}
    vector<vector<string>> anomalyResults;

    // Analyze soil data and detect anomalies
    for (const auto& data : soilData)
    {

        int sampleID = static_cast<int>(data[0]);
        float pH = data[1];
        float moisture = data[2];
        float pollution = data[3];

        string anomalyFlag = "Normal";

        // Check for anomalies
        if (pH < PH_THRESHOLD_LOW || pH > PH_THRESHOLD_HIGH)

        {
            anomalyFlag = "Anomaly (pH)";
        }
        if (moisture < MOISTURE_THRESHOLD_LOW || moisture > MOISTURE_THRESHOLD_HIGH)
        {
            anomalyFlag = "Anomaly (Moisture)";
        }
        if (pollution > POLLUTION_THRESHOLD)
        {
            anomalyFlag = "Anomaly (Pollution)";
        }

        // Store the result
        anomalyResults.push_back({
            to_string(sampleID),
            to_string(pH),
            to_string(moisture),
            to_string(pollution),
            anomalyFlag
        });
    }

    // Display results in table form
    vector<string> headers = {"Sample ID", "pH", "Moisture Content (%)", "Pollution Level", "Anomaly Status"};
    printTable(anomalyResults, headers);

    cout << "Anomaly detection completed.\nPress any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}


//--------------------------------------------------------------------------------------

void forecastFuturePollutionLevels()
{
    cout << "Forecast Future Pollution Levels: Predicting future levels of contamination..." << endl;

    // Simulated historical pollution data for a given region (this could be from sensors over time)
    vector<pair<int, float>> historicalData =
    {
        {1, 50.0},  // Day 1, Pollution Level = 50
        {2, 60.0},  // Day 2, Pollution Level = 60
        {3, 65.0},  // Day 3, Pollution Level = 65
        {4, 75.0},  // Day 4, Pollution Level = 75
        {5, 85.0},  // Day 5, Pollution Level = 85
        {6, 95.0},  // Day 6, Pollution Level = 95
        {7, 100.0}  // Day 7, Pollution Level = 100
    };

    // Simple forecasting method (linear regression approximation for demonstration)
    float slope = 0.0, intercept = 0.0;
    int n = historicalData.size();

    // Calculate the slope and intercept for a linear equation: y = mx + b
    float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    for (const auto& data : historicalData)
    {
        sumX += data.first;
        sumY += data.second;
        sumXY += data.first * data.second;
        sumX2 += data.first * data.first;
    }

    slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    intercept = (sumY - slope * sumX) / n;

    // Forecasting future pollution levels for the next 3 days
    cout << "\nForecasted Pollution Levels for the Next 3 Days:\n";
    for (int day = 8; day <= 10; ++day)
    {
        float forecastedLevel = slope * day + intercept;
        cout << "Day " << day << ": Pollution Level = " << fixed << setprecision(2) << forecastedLevel << " (Forecasted)" << endl;
    }

    cout << "\nFuture pollution level forecasting completed.\n Press any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();
}


//--------------------------------------------------------------------------------------

void userAuthenticationModule() {
    cout << "NO USER FOUND THIS MODAL" << endl;
    cin.ignore();
    cin.get();
}
//--------------------------------------------------------------------------------------

void dataStorageModule() {
    cout << "Data Storage Module: Fetching soil data from the file..." << endl;

    string filePath = "D:\\DAA Airawar Project\\soil_data.txt";
    ifstream inputFile(filePath);

    if (inputFile.is_open()) {
        cout << "Soil Data from file (" << filePath << "):\n" << endl;

        string line;
        while (getline(inputFile, line)) {
            cout << line << endl;
        }

        inputFile.close();
    } else {
        cerr << "Error: Unable to open file at " << filePath << endl;
    }

    cout << "\nPress any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();
}

//--------------------------------------------------------------------------------------

void alertSystem()
{
    cout << "Alert System: Notifying users of critical soil conditions..." << endl;

    // Ask the user to input threshold values for pH, moisture, and pollution levels
    float PH_THRESHOLD_LOW, PH_THRESHOLD_HIGH, MOISTURE_THRESHOLD_LOW, MOISTURE_THRESHOLD_HIGH, POLLUTION_THRESHOLD;

    cout << endl;

    cout << "Enter the low threshold for pH: ";
    cin >> PH_THRESHOLD_LOW;
    cout << "Enter the high threshold for pH: ";
    cin >> PH_THRESHOLD_HIGH;

    cout << "Enter the low threshold for Moisture Content (%): ";
    cin >> MOISTURE_THRESHOLD_LOW;
    cout << "Enter the high threshold for Moisture Content (%): ";
    cin >> MOISTURE_THRESHOLD_HIGH;

    cout << "Enter the threshold for Pollution Level: ";
    cin >> POLLUTION_THRESHOLD;

    // Sample soil data: {Sample ID, pH, Moisture Content, Pollution Level}
    vector<vector<float>> soilData =
    {
        {1, 6.5, 40.0, 50.0},   // Normal data
        {2, 7.0, 45.0, 120.0},  // Moderate data
        {3, 5.5, 30.0, 200.0},  // Possible anomaly (high pollution)
        {4, 6.2, 35.0, 45.0},   // Normal data
        {5, 8.0, 50.0, 400.0},  // Anomaly (high pollution)
        {6, 6.7, 42.0, 100.0},  // Normal data
        {7, 7.5, 38.0, 250.0}   // Anomaly (high pollution)
    };

    // Checking the soil data and issuing alerts if the conditions cross the threshold
    cout << endl;
    for (const auto& data : soilData)

    {
        int sampleID = data[0];
        float pH = data[1];
        float moisture = data[2];
        float pollution = data[3];



        cout << "Sample ID: " << sampleID << " - ";

        // Checking for pH anomalies
        if (pH < PH_THRESHOLD_LOW || pH > PH_THRESHOLD_HIGH)
        {
            cout << "ALERT: pH level out of range!";
        }

        // Checking for moisture anomalies
        if (moisture < MOISTURE_THRESHOLD_LOW || moisture > MOISTURE_THRESHOLD_HIGH)
        {
            cout << "ALERT: Moisture level out of range!";
        }

        // Checking for pollution anomalies
        if (pollution > POLLUTION_THRESHOLD)
        {
            cout << "ALERT: Pollution level exceeds critical threshold!";
        }

        // If no critical values, display normal status
        if ((pH >= PH_THRESHOLD_LOW && pH <= PH_THRESHOLD_HIGH) &&
            (moisture >= MOISTURE_THRESHOLD_LOW && moisture <= MOISTURE_THRESHOLD_HIGH) &&
            pollution <= POLLUTION_THRESHOLD)
        {
            cout << "Status: Normal";
        }

        cout << endl;  // Print a newline after each sample's check
    }

    cout << endl;

    cout << "Alert system completed." << endl;

    cout << "Press any key to return to the main menu." << endl;

    cin.ignore();
    cin.get();
}

//-----------------------------------------------------------------------

void waterPollutionMonitoring() {
    // ANSI escape codes for different colors
    const string boldBlue = "\033[1;34m";    // Bold Blue
    const string red = "\033[1;31m";         // Red
    const string pink = "\033[1;35m";        // Pink
    const string reset = "\033[0m";          // Reset formatting

    int choice;
    while (true) {
        cout << "-----------------------------------------\n";
        cout << "\nWater Pollution Monitoring Modules:\n";
        cout << "-----------------------------------------\n";


        // Menu items in Bold Blue
        cout << boldBlue << "\n1. Data Collection Module\n";
        cout << "2. Water Quality Index (WQI) Calculation\n";
        cout << "3. Pollutant Detection and Classification\n";
        cout << "4. Real-Time Monitoring and Alert System\n";
        cout << "5. Contamination Source Tracking\n";
        cout << "6. Pollution Spread Prediction\n";
        cout << "7. Classification of Water Quality\n";
        cout << "8. Forecast Future Water Quality\n";
        cout << "9. Remediation Recommendation\n";
        cout << "10. Visualization and Reporting\n";

        // Option 11 in Red
        cout << red << "11. Return to Main Menu\n" << reset;

        // Input prompt in Pink
        cout << pink << "\nEnter your choice: " << reset;
        cout << pink << "\n" << reset;

        cin >> choice;

        switch (choice) {
            case 1:
                dataCollectionModule22();  // Assuming function is defined elsewhere
                break;
            case 2:
                waterQualityIndexCalculation();  // Assuming function is defined elsewhere
                break;
            case 3:
                pollutantDetectionAndClassification();  // Assuming function is defined elsewhere
                break;
            case 4:
                realTimeMonitoringAndAlertSystem();  // Assuming function is defined elsewhere
                break;
            case 5:
                contaminationSourceTracking();  // Assuming function is defined elsewhere
                break;
            case 6:
                pollutionSpreadPrediction();  // Assuming function is defined elsewhere
                break;
            case 7:
                classificationOfWaterQuality();  // Assuming function is defined elsewhere
                break;
            case 8:
                forecastFutureWaterQuality();  // Assuming function is defined elsewhere
                break;
            case 9:
                remediationRecommendation();  // Assuming function is defined elsewhere
                break;
            case 10:
                visualizationAndReporting();  // Assuming function is defined elsewhere
                break;
            case 11:
                return;  // Return to main menu
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

//---------------------------------------------------------------------------------------

void dataCollectionModule22()
{
    cout << "Data Collection Module: Collecting water quality parameters (pH, turbidity, dissolved oxygen, pollutant levels)..." << endl;

    const int numInputs = 20; // Number of inputs
    vector<float> pHValues = {7.2, 6.8, 7.5, 7.1, 6.9, 7.3, 6.7, 7.6, 7.2, 6.8, 7.4, 6.9, 7.1, 7.3, 6.6, 7.5, 7.0, 6.8, 7.2, 7.4};
    vector<float> turbidityValues = {12.5, 15.1, 10.8, 14.2, 18.5, 11.2, 16.8, 9.7, 13.4, 19.1, 10.5, 17.6, 12.0, 11.7, 20.3, 9.9, 14.6, 18.2, 13.0, 10.2};
    vector<float> dissolvedOxygenValues = {6.8, 5.9, 7.2, 6.5, 5.7, 6.9, 5.6, 7.4, 6.7, 5.5, 7.0, 5.8, 6.4, 6.6, 5.4, 7.1, 6.3, 5.7, 6.5, 7.2};
    vector<float> pollutantLevels = {0.03, 0.07, 0.02, 0.04, 0.08, 0.03, 0.06, 0.01, 0.04, 0.09, 0.02, 0.07, 0.04, 0.03, 0.10, 0.01, 0.05, 0.08, 0.03, 0.02};

    // Displaying collected data in a table format
    cout << "\nData Collection Completed. Here are the collected parameters:\n";

    cout << string(70, '-') << endl; // Separator line

    cout << left << setw(10) << "Sample"
         << setw(10) << "pH"
         << setw(15) << "Turbidity (NTU)"
         << setw(20) << "Dissolved O2 (mg/L)"
         << setw(15) << "Pollutant (mg/L)" << endl;

    cout << string(70, '-') << endl; // Separator line

    for (int i = 0; i < numInputs; ++i)
    {

        cout << left << setw(10) << (i + 1)
             << setw(10) << pHValues[i]
             << setw(15) << turbidityValues[i]
             << setw(20) << dissolvedOxygenValues[i]
             << setw(15) << pollutantLevels[i] << endl;
    }

    cout << "\n" << endl;
    cout << "Press Enter to return to the main menu." << endl;

    cin.ignore();

    cin.get();
}

//---------------------------------------------------------------------------------------


void waterQualityIndexCalculation()
{
    // Sample data (directly included in the function)
    vector<float> pHValues = {7.2, 6.8, 7.5, 7.1, 6.9, 7.3, 6.7, 7.6, 7.2, 6.8,
                              7.4, 6.9, 7.1, 7.3, 6.6, 7.5, 7.0, 6.8, 7.2, 7.4};

    vector<float> turbidityValues = {12.5, 15.1, 10.8, 14.2, 18.5, 11.2, 16.8, 9.7, 13.4, 19.1,
                                     10.5, 17.6, 12.0, 11.7, 20.3, 9.9, 14.6, 18.2, 13.0, 10.2};

    vector<float> dissolvedOxygenValues = {6.8, 5.9, 7.2, 6.5, 5.7, 6.9, 5.6, 7.4, 6.7, 5.5,
                                           7.0, 5.8, 6.4, 6.6, 5.4, 7.1, 6.3, 5.7, 6.5, 7.2};

    vector<float> pollutantLevels = {0.03, 0.07, 0.02, 0.04, 0.08, 0.03, 0.06, 0.01, 0.04, 0.09,
                                     0.02, 0.07, 0.04, 0.03, 0.10, 0.01, 0.05, 0.08, 0.03, 0.02};

    const int numInputs = pHValues.size(); // Number of samples

    vector<float> wqiValues(numInputs);   // Vector to store calculated WQI values

    // Weight factors for parameters
    const float pHWeight = 0.25;

    const float turbidityWeight = 0.25;

    const float dissolvedOxygenWeight = 0.3;

    const float pollutantWeight = 0.2;

    // Ideal ranges for parameters (assumed for this example)

    const float idealPH = 7.0;

    const float idealTurbidity = 5.0;

    const float idealDissolvedOxygen = 8.0;

    const float idealPollutantLevel = 0.0;

    // Calculating WQI for each sample
    for (int i = 0; i < numInputs; ++i)
    {
        // Calculate parameter sub-indices (lower deviation = better quality)
        float pHIndex = max(0.0f, 100.0f - abs(pHValues[i] - idealPH) * 10.0f); // Use 10.0f for float
        float turbidityIndex = max(0.0f, 100.0f - turbidityValues[i] * 2.0f); // Use 2.0f for float
        float dissolvedOxygenIndex = max(0.0f, 100.0f - abs(dissolvedOxygenValues[i] - idealDissolvedOxygen) * 12.5f); // Use 12.5f for float
        float pollutantIndex = max(0.0f, 100.0f - pollutantLevels[i] * 10.0f); // Use 10.0f for float

        // Weighted sum to calculate WQI
        wqiValues[i] = (pHIndex * pHWeight) +
                       (turbidityIndex * turbidityWeight) +
                       (dissolvedOxygenIndex * dissolvedOxygenWeight) +
                       (pollutantIndex * pollutantWeight);
    }

    // Display the WQI results
    cout << "\nWater Quality Index (WQI) Calculation Results:\n";

    cout << string(25, '-') << endl; // Separator line

    cout << left << setw(10) << "Sample"
         << setw(15) << "WQI (0-100)" << endl;

    cout << string(25, '-') << endl; // Separator line

    // Display the WQI for each sample
    for (int i = 0; i < numInputs; ++i)
    {
        cout << left << setw(10) << (i + 1)
             << setw(15) << fixed << setprecision(2) << wqiValues[i] << endl;
    }

    cout << "\nWQI Calculation Completed." << endl;
}


//--------------------------------------------------------------------------------------------------------



void pollutantDetectionAndClassification()
{

    cout << "Pollutant Detection and Classification Module: (Using threshold-based logic)" << endl;

    // Number of samples to classify
    const int numSamples = 3;

    // Vectors to store user input values for each sample
    vector<float> pH(numSamples);

    vector<float> turbidity(numSamples);

    vector<float> dissolvedOxygen(numSamples);

    vector<float> pollutantLevel(numSamples);

    // Collect data from user
    for (int i = 0; i < numSamples; ++i)
    {
        cout << "\nEnter data for Sample " << (i + 1) << ":" << endl;

        // Input pH value
        cout << "Enter pH value (0-14): ";
        cin >> pH[i];

        // Input turbidity value
        cout << "Enter turbidity value (0-100 NTU): ";
        cin >> turbidity[i];

        // Input dissolved oxygen value
        cout << "Enter dissolved oxygen value (0-20 mg/L): ";
        cin >> dissolvedOxygen[i];

        // Input pollutant level value
        cout << "Enter pollutant level value (0-1000 mg/L): ";
        cin >> pollutantLevel[i];
    }

    // Output classification for each sample
    for (int i = 0; i < numSamples; ++i)
    {
        string classification;

        // Pollutant classification logic directly in the loop
        if (pH[i] < 6.0 || turbidity[i] > 50 || dissolvedOxygen[i] < 4.0 || pollutantLevel[i] > 500)
        {
            classification = "High Pollution";
        }
        else if ((pH[i] >= 6.0 && pH[i] <= 7.5) && turbidity[i] <= 50 && dissolvedOxygen[i] >= 4.0 && pollutantLevel[i] <= 300)
        {
            classification = "Medium Pollution";
        }
        else
        {
            classification = "Low Pollution";
        }

        // Displaying the classification and the values

        cout << "\nSample " << (i + 1) << " Classification: " << classification << endl;

        cout << "pH: " << pH[i] << ", Turbidity: " << turbidity[i] << " NTU, Dissolved Oxygen: "
             << dissolvedOxygen[i] << " mg/L, Pollutant Level: " << pollutantLevel[i] << " mg/L" << endl;
    }
}



//--------------------------------------------------------------------------------------------




void realTimeMonitoringAndAlertSystem()
 {
    cout << "Real-Time Monitoring and Alert System Module: (Monitoring water quality in real time)" << endl;

    // Thresholds for water quality parameters
    const float pHThresholdLow = 6.0;

    const float pHThresholdHigh = 8.5;

    const float turbidityThreshold = 50.0;  // NTU

    const float dissolvedOxygenThresholdLow = 4.0;  // mg/L

    const float pollutantLevelThreshold = 500.0;  // mg/L

    // Simulated real-time data for monitoring (values would come from sensors in a real system)
    vector<float> pH = {6.5, 5.8, 8.0, 7.2, 5.0};  // pH values

    vector<float> turbidity = {20.0, 55.0, 45.0, 10.0, 60.0};  // Turbidity (NTU)

    vector<float> dissolvedOxygen = {7.0, 3.5, 8.5, 4.5, 3.0};  // Dissolved oxygen (mg/L)

    vector<float> pollutantLevel = {100.0, 600.0, 200.0, 100.0, 700.0};  // Pollutant levels (mg/L)

    // Real-time simulation loop (simulating monitoring over time)
    for (int i = 0; i < 5; ++i)
    {
        // Display the current sample data
        cout << "\nMonitoring Sample " << (i + 1) << "..." << endl;

        cout << "pH: " << pH[i] << ", Turbidity: " << turbidity[i] << " NTU, Dissolved Oxygen: "
             << dissolvedOxygen[i] << " mg/L, Pollutant Level: " << pollutantLevel[i] << " mg/L" << endl;

        // Check if any parameter exceeds the threshold, triggering an alert
        if (pH[i] < pHThresholdLow || pH[i] > pHThresholdHigh)
        {
            cout << "ALERT: pH value out of range!" << endl;
        }
        if (turbidity[i] > turbidityThreshold)
        {
            cout << "ALERT: Turbidity level too high!" << endl;
        }
        if (dissolvedOxygen[i] < dissolvedOxygenThresholdLow)
        {
            cout << "ALERT: Dissolved oxygen level too low!" << endl;
        }
        if (pollutantLevel[i] > pollutantLevelThreshold)
        {
            cout << "ALERT: Pollutant level too high!" << endl;
        }

        // Simulate a real-time delay (for example, 2 seconds between checks)
        this_thread::sleep_for(chrono::seconds(2));
    }

    cout << "\nReal-time monitoring completed." << endl;
}


//----------------------------------------------------------------------------------------------




void contaminationSourceTracking()
{



    cout << "Contamination Source Tracking Module: (Tracking pollution sources based on water quality data)" << endl;

    // Simulated contamination sources and their characteristics
    vector<string> sources = {"Industrial Waste", "Agricultural Runoff", "Sewage Leak", "Construction Site"};

    vector<string> possibleContaminants = {"Heavy Metals", "Nutrients", "Pathogens", "Sediment"};

    // Simulated data (sample water quality readings and locations)
    vector<vector<float>> waterQualityData = {
        {6.5, 20.0, 7.0, 100.0}, // Sample 1: pH, Turbidity, Dissolved Oxygen, Pollutant Level
        {5.8, 55.0, 3.5, 600.0}, // Sample 2
        {8.0, 45.0, 8.5, 200.0}, // Sample 3
        {7.2, 10.0, 4.5, 100.0}, // Sample 4
        {5.0, 60.0, 3.0, 700.0}  // Sample 5
    };

    // Tracking the potential source of contamination
    for (int i = 0; i < waterQualityData.size(); ++i)
    {

        cout << "\nMonitoring Sample " << (i + 1) << "..." << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

        // Extract the sample's water quality data
        float pH = waterQualityData[i][0];

        float turbidity = waterQualityData[i][1];

        float dissolvedOxygen = waterQualityData[i][2];

        float pollutantLevel = waterQualityData[i][3];

        // Simulating contamination source tracking logic based on thresholds
        string source = "Unknown Source";

        string contaminants = "Unknown Contaminants";

        // Source determination based on water quality parameters (simplified logic)
        if (pollutantLevel > 500.0 && turbidity > 50.0)
        {
            source = sources[0];  // Industrial Waste
            contaminants = possibleContaminants[0] + ", " + possibleContaminants[3];  // Heavy Metals, Sediment
        }
        else if (pH < 6.0 && turbidity > 30.0)
        {
            source = sources[1];  // Agricultural Runoff
            contaminants = possibleContaminants[1] + ", " + possibleContaminants[3];  // Nutrients, Sediment
        }
        else if (dissolvedOxygen < 4.0 && pollutantLevel > 600.0)
        {
            source = sources[2];  // Sewage Leak
            contaminants = possibleContaminants[2] + ", " + possibleContaminants[3];  // Pathogens, Sediment
        }
        else if (turbidity > 40.0)
        {
            source = sources[3];  // Construction Site
            contaminants = possibleContaminants[3];  // Sediment
        }

        // Displaying the results
        cout << "Water Quality - pH: " << pH << ", Turbidity: " << turbidity << " NTU, Dissolved Oxygen: "
             << dissolvedOxygen << " mg/L, Pollutant Level: " << pollutantLevel << " mg/L" << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

        cout << "Possible Contamination Source: " << source << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

        cout << "Possible Contaminants: " << contaminants << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

    }


    cout << "\nContamination source tracking completed." << endl;
}




//----------------------------------------------------------------------------------------------------------------------------------




void pollutionSpreadPrediction()
{
    cout << "Pollution Spread Prediction Module: (Predicting pollutant dispersion based on water quality data)" << endl;

    // Simulated data for pollution spread (e.g., starting pollutant levels at different locations)
    vector<float> initialPollutantLevels = {100.0, 150.0, 200.0, 300.0}; // Pollutant levels in mg/L at different locations

    vector<float> flowRates = {0.5, 0.7, 1.2, 0.3}; // Water flow rates in m/s at different locations

    vector<float> timeIntervals = {1.0, 2.0, 3.0, 4.0}; // Time intervals in hours

    // Simulated pollution spread prediction logic
    for (int i = 0; i < initialPollutantLevels.size(); ++i)
    {
        cout << "\nPredicting pollution spread for Location " << (i + 1) << "..." << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Delay for 1 second

        // Basic pollution spread model: Pollution spreads based on flow rate and time
        float pollutionSpread = initialPollutantLevels[i] * flowRates[i] * timeIntervals[i];

        float newPollutantLevel = initialPollutantLevels[i] + pollutionSpread;

        // Displaying the results of the pollution spread prediction
        cout << "Initial Pollutant Level at Location " << (i + 1) << ": " << initialPollutantLevels[i] << " mg/L" << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Delay for 1 second

        cout << "Flow Rate at Location " << (i + 1) << ": " << flowRates[i] << " m/s" << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Delay for 1 second

        cout << "Time Interval: " << timeIntervals[i] << " hours" << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Delay for 1 second

        cout << "Predicted Pollutant Level after Spread: " << newPollutantLevel << " mg/L" << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Delay for 1 second
    }

    cout << "\nPollution spread prediction completed." << endl;
}


//-------------------------------------------------------------------------------------------------------------------



void classificationOfWaterQuality()
 {

    cout << "Classification of Water Quality Module: (Classifying water quality based on parameters)" << endl;

    // Simulated data for water samples (pH, turbidity, dissolved oxygen, pollutant levels)
    vector<vector<float>> waterQualityData =
    {
        {7.2, 20.0, 8.5, 50.0}, // Sample 1: pH, Turbidity (NTU), Dissolved Oxygen (mg/L), Pollutant Level (mg/L)
        {5.8, 60.0, 3.5, 200.0}, // Sample 2
        {8.0, 10.0, 9.0, 10.0},  // Sample 3
        {6.5, 30.0, 4.5, 150.0}, // Sample 4
        {4.0, 70.0, 2.0, 500.0}  // Sample 5
    };

    // Classification thresholds for water quality
    const float pHLow = 6.5, pHHigh = 8.5; // pH range for "Good" water quality

    const float turbidityLow = 5.0, turbidityHigh = 30.0; // NTU range for "Good" water quality

    const float dissolvedOxygenLow = 5.0; // mg/L for "Good" oxygen levels

    const float pollutantLow = 100.0, pollutantHigh = 500.0; // mg/L range for "Moderate" pollution levels

    // Classifying water quality based on parameters
    for (int i = 0; i < waterQualityData.size(); ++i)
    {
        cout << "\nClassifying Sample " << (i + 1) << "..." << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

        // Extracting parameters for the current sample
        float pH = waterQualityData[i][0];

        float turbidity = waterQualityData[i][1];

        float dissolvedOxygen = waterQualityData[i][2];

        float pollutantLevel = waterQualityData[i][3];

        // Classifying based on parameter ranges
        string waterQuality;

        if (pH >= pHLow && pH <= pHHigh && turbidity <= turbidityHigh && dissolvedOxygen >= dissolvedOxygenLow && pollutantLevel <= pollutantHigh)
        {
            waterQuality = "Excellent";
        }
        else if (pH >= 6.0 && pH <= 8.0 && turbidity <= 50.0 && dissolvedOxygen >= 4.0 && pollutantLevel <= 300.0)
        {
            waterQuality = "Good";
        }
        else if (pH >= 5.0 && pH <= 9.0 && turbidity <= 75.0 && dissolvedOxygen >= 2.0 && pollutantLevel <= 500.0)
        {
            waterQuality = "Moderate";
        }
        else
        {
            waterQuality = "Poor";
        }

        // Displaying the classification results
        cout << "Water Quality Classification: " << waterQuality << endl;

        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

        cout << "Sample " << (i + 1) << " - pH: " << pH << ", Turbidity: " << turbidity << " NTU, Dissolved Oxygen: "
             << dissolvedOxygen << " mg/L, Pollutant Level: " << pollutantLevel << " mg/L" << endl;
        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second
    }

    cout << "\nWater quality classification completed." << endl;
}

//-------------------------------------------------------------------------------------------------------------------------

void forecastFutureWaterQuality()
{
    cout << "Forecast Future Water Quality Module: (Forecasting water quality trends based on historical data)" << endl;

    // Simulated historical water quality data (e.g., pH values over 5 days)
    vector<float> historicalData = {7.0, 7.2, 7.4, 7.6, 7.8}; // Example: pH values over 5 days

    // Display historical data in table format
    cout << "\nHistorical Water Quality Data (pH values):\n";

    cout << left << setw(10) << "Day" << setw(20) << "pH Value" << endl;

    cout << string(30, '-') << endl; // Separator line

    for (int i = 0; i < historicalData.size(); ++i)
    {
        cout << left << setw(10) << (i + 1) << setw(20) << historicalData[i] << endl;
    }

    // Calculating the average rate of change in the historical data
    float totalChange = 0.0;

    for (int i = 1; i < historicalData.size(); ++i)
    {
        totalChange += historicalData[i] - historicalData[i - 1];
    }

    float rateOfChange = totalChange / (historicalData.size() - 1);

    cout << "\nRate of change in water quality (pH): " << rateOfChange << " units per day" << endl;

    this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second

    // Forecasting future water quality for the next 3 days
    int forecastDays = 3;

    cout << "\nForecasting water quality for the next " << forecastDays << " days...\n";

    cout << left << setw(10) << "Day" << setw(20) << "Forecasted pH" << endl;

    cout << string(30, '-') << endl; // Separator line

    // Predicting future values and displaying them in a table format
    for (int i = 1; i <= forecastDays; ++i)
    {
        float predictedValue = historicalData[historicalData.size() - 1] + rateOfChange * i;

        cout << left << setw(10) << (historicalData.size() + i) << setw(20) << predictedValue << endl;

        this_thread::sleep_for(chrono::seconds(1));  // Delay for 1 second
    }

    // Ask the user to input the current water quality (pH value)
    float currentWaterQuality;

    cout << "\nEnter current pH value: ";

    cin >> currentWaterQuality;

    // Display result based on the current water quality (pH)
    string result = (currentWaterQuality >= 6.5 && currentWaterQuality <= 8.5) ? "Good" : "Bad";

    cout << "\nCurrent Water Quality is: " << result << endl;

    cout << "\nFuture water quality forecasting completed." << endl;
}


//---------------------------------------------------------------------------------------------------------------------------

void remediationRecommendation()
{
    cout << "Remediation Recommendation Module: (Recommending remediation methods based on water quality parameters)" << endl;

    // Simulating input values for water quality parameters (user can modify these based on their readings)
    float pH, turbidity, dissolvedOxygen, pollutantLevel;

    // Input water quality parameters
    cout << "Enter current pH value: ";
    cin >> pH;

    cout << "Enter current turbidity value (NTU): ";
    cin >> turbidity;

    cout << "Enter current dissolved oxygen level (mg/L): ";
    cin >> dissolvedOxygen;

    cout << "Enter current pollutant level (mg/L): ";
    cin >> pollutantLevel;

    // Providing remediation recommendations based on input values
    cout << "\nRemediation Recommendations based on water quality parameters:\n";

    cout << left << setw(25) << "Water Quality Parameter" << setw(25) << "Current Value" << setw(30) << "Remediation Recommendation" << endl;
    cout << string(80, '-') << endl;

    // pH-based recommendation

    if (pH < 6.5)
    {
        cout << left << setw(25) << "pH (acidic)" << setw(25) << pH << setw(30) << "Use neutralizing agents like lime or soda ash." << endl;
    }

    else if (pH > 8.5)
    {
        cout << left << setw(25) << "pH (alkaline)" << setw(25) << pH << setw(30) << "Add acidic compounds like sulfuric acid." << endl;
    }

    else
    {
        cout << left << setw(25) << "pH (neutral)" << setw(25) << pH << setw(30) << "Water quality is within normal range for pH." << endl;
    }

    // Turbidity-based recommendation

    if (turbidity > 5.0)
    {
        cout << left << setw(25) << "Turbidity" << setw(25) << turbidity << setw(30) << "Use coagulation and flocculation, followed by filtration." << endl;
    }

   else
    {
        cout << left << setw(25) << "Turbidity" << setw(25) << turbidity << setw(30) << "Turbidity levels are within acceptable range." << endl;
    }

    // Dissolved Oxygen-based recommendation
    if (dissolvedOxygen < 5.0)
    {
        cout << left << setw(25) << "Dissolved Oxygen" << setw(25) << dissolvedOxygen << setw(30) << "Increase aeration or use oxygenation systems." << endl;
    }
    else
    {
        cout << left << setw(25) << "Dissolved Oxygen" << setw(25) << dissolvedOxygen << setw(30) << "Dissolved oxygen levels are sufficient." << endl;
    }

    // Pollutant Level-based recommendation
    if (pollutantLevel > 500.0)
    {
        cout << left << setw(25) << "Pollutant Level" << setw(25) << pollutantLevel << setw(30) << "Use advanced filtration or chemical treatment." << endl;
    }
    else
    {
        cout << left << setw(25) << "Pollutant Level" << setw(25) << pollutantLevel << setw(30) << "Pollutant level is within acceptable range." << endl;
    }


    cout << "\nRemediation recommendation process completed." << endl;
}


//--------------------------------------------------------------------------------------------------

// Function to simulate visualization and generate reports for stakeholders
void visualizationAndReporting()
{

    cout << "Visualization and Reporting Module: Generating visualizations and reports for stakeholders...\n";

    // Simulating data for water quality parameters
    vector<float> pHValues = {6.5, 7.2, 6.8, 7.0, 6.9};

    vector<float> turbidityValues = {10.5, 8.3, 5.7, 4.0, 9.0};

    vector<float> dissolvedOxygenValues = {4.5, 7.0, 5.3, 6.0, 4.8};

    vector<float> pollutantLevels = {300.0, 400.0, 150.0, 500.0, 450.0};

    // Simulating a report generation
    cout << "\nGenerating Water Quality Report...\n";

    cout << string(50, '-') << endl;

    cout << left << setw(25) << "Sample Number"
         << setw(10) << "pH"
         << setw(20) << "Turbidity (NTU)"
         << setw(20) << "Dissolved O2 (mg/L)"
         << setw(20) << "Pollutant Level (mg/L)" << endl;

    cout << string(50, '-') << endl;

    for (int i = 0; i < 5; ++i)
    {
        cout << left << setw(25) << "Sample " + to_string(i+1)
             << setw(10) << pHValues[i]
             << setw(20) << turbidityValues[i]
             << setw(20) << dissolvedOxygenValues[i]
             << setw(20) << pollutantLevels[i] << endl;
    }

    cout << "\nEnd of Report.\n";

    // Simple visualization using ASCII art
    cout << "\nGenerating Visual Representation (Bar Chart Example)...\n";

    cout << string(50, '-') << endl;
    cout << "pH Values:\n";

    for (const float& value : pHValues)
    {
        cout << string(int(value * 2), '*') << " " << value << endl; // Visualize pH as a bar chart
    }

    cout << "\nTurbidity Values:\n";

    for (const float& value : turbidityValues)
    {
        cout << string(int(value / 2), '*') << " " << value << endl; // Visualize turbidity as a bar chart
    }

    cout << "\nDissolved Oxygen Values:\n";

    for (const float& value : dissolvedOxygenValues)
    {
        cout << string(int(value * 2), '*') << " " << value << endl; // Visualize dissolved oxygen as a bar chart
    }

    cout << "\nPollutant Levels:\n";

    for (const float& value : pollutantLevels)
    {
        cout << string(int(value / 10), '*') << " " << value << endl; // Visualize pollutant levels as a bar chart
    }


cout << "\nVisualization and Reporting Completed.\n";
}