#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Base class for lab equipment
class LabEquipment
{
protected:
    string name;
    string manufacturer;

public:
    LabEquipment(const string &name, const string &manufacturer)
        : name(name), manufacturer(manufacturer) {}

    virtual void printDetails() const = 0; // Pure virtual function

    const string &getName() const
    {
        return name;
    }

    const string &getManufacturer() const
    {
        return manufacturer;
    }
};

// Derived class for a centrifuge
class Centrifuge : public LabEquipment
{
private:
    int maxSpeed;

public:
    Centrifuge(const string &name, const string &manufacturer, int maxSpeed)
        : LabEquipment(name, manufacturer), maxSpeed(maxSpeed) {}

    void printDetails() const override
    {
        cout << "Centrifuge: " << name << ", Manufacturer: " << manufacturer
             << ", Max Speed: " << maxSpeed << " RPM" << endl;
    }
};

// Derived class for a spectrophotometer
class Spectrophotometer : public LabEquipment
{
private:
    double wavelengthRange;

public:
    Spectrophotometer(const string &name, const string &manufacturer, double wavelengthRange)
        : LabEquipment(name, manufacturer), wavelengthRange(wavelengthRange) {}

    void printDetails() const override
    {
        cout << "Spectrophotometer: " << name << ", Manufacturer: " << manufacturer
             << ", Wavelength Range: " << wavelengthRange << " nm" << endl;
    }
};

// Template class for a container of lab equipment
template <typename T>
class LabInventory
{
private:
    T *equipment;
    int capacity;
    int size;

public:
    LabInventory(int capacity)
        : capacity(capacity), size(0)
    {
        equipment = new T[capacity];
    }

    ~LabInventory()
    {
        delete[] equipment;
    }

    void addEquipment(const T &item)
    {
        if (size < capacity)
        {
            equipment[size++] = item;
        }
    }

    void printInventory() const
    {
        for (int i = 0; i < size; i++)
        {
            equipment[i]->printDetails();
        }
    }

    const T &getEquipment(int index) const
    {
        return equipment[index];
    }

    int getSize() const
    {
        return size;
    }
};

int main()
{
    cout << "Welcome to the Lab Management System!" << endl;

    LabInventory<LabEquipment *> lab(10);

    while (true)
    {
        cout << "\nPlease select an option:" << endl;
        cout << "1. Add Lab Equipment" << endl;
        cout << "2. Display Inventory" << endl;
        cout << "3. Save Inventory" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\nEnter the equipment type (1 for Centrifuge, 2 for Spectrophotometer): ";
            int type;
            cin >> type;

            cout << "Enter the name: ";
            string name;
            cin.ignore();
            getline(cin, name);

            cout << "Enter the manufacturer: ";
            string manufacturer;
            getline(cin, manufacturer);

            if (type == 1)
            {
                cout << "Enter the maximum speed (RPM): ";
                int maxSpeed;
                cin >> maxSpeed;

                lab.addEquipment(new Centrifuge(name, manufacturer, maxSpeed));
            }
            else if (type == 2)
            {
                cout << "Enter the wavelength range (nm): ";
                double wavelengthRange;
                cin >> wavelengthRange;

                lab.addEquipment(new Spectrophotometer(name, manufacturer, wavelengthRange));
            }
            else
            {
                cout << "Invalid equipment type. Please try again." << endl;
            }

            cout << "Lab equipment added successfully!" << endl;
            break;
        }

        case 2:
        {
            cout << "\nInventory:" << endl;
            lab.printInventory();
            break;
        }

        case 3:
        {
            ofstream outputFile("inventory.txt");
            if (!outputFile)
            {
                cerr << "Failed to open output file." << endl;
                break;
            }

            for (int i = 0; i < lab.getSize(); i++)
            {
                outputFile << lab.getEquipment(i)->getName() << ", "
                           << lab.getEquipment(i)->getManufacturer() << endl;
            }

            outputFile.close();

            cout << "\nInventory saved to 'inventory.txt'." << endl;
            break;
        }

        case 4:
        {
            cout << "\nExiting the Lab Management System. Goodbye!" << endl;
            return 0;
        }

        default:
        {
            cout << "\nInvalid choice. Please try again." << endl;
        }
        }
    }
}
