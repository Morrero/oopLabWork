#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <iomanip>
#include <list>
#include <unordered_map>
#include <algorithm>


using namespace std;

bool LicensePlateCheck(char* string);
bool stringCheck(char* string);
void InputPositiveNumber(int& number, string msg, int max_value);
void InputPositiveNumber(unsigned int& number, string msg, unsigned int max_value);
void InputPositiveNumber(float& number, string msg, float max_value);
void InputLicensePlate(char* str, string msg);
void InputString(char* str, string msg);
void InputYear(unsigned int& number, string msg);

void clearFile(const char* FILE_NAME);

enum AutotransportType { passenger, cargo };

class Transport {
protected:
	char name[5];
public:
	Transport() {
		strcpy_s(name, "N/A");
	}
	Transport(char name[]) {
		strcpy_s(this->name, name);
	}
	Transport(const char name[]) {
		strcpy_s(this->name, name);
	}
	void SetName(char name[]) {
		strcpy_s(this->name, name);
	}
	char* GetName() {
		return name;
	}
	virtual void Input() {}
	virtual void Output() {}
};
class Autotransport :public Transport {
protected:
	char license_plate[14];
	char brand[16];
	unsigned int release_year;
	char engine_type[15];
	float engine_volume;
	int max_speed;
public:
	Autotransport() :Transport("авто") {
		strcpy_s(name, "авто");
		strcpy_s(license_plate, "N/A");
		strcpy_s(brand, "N/A");
		release_year = 0;
		strcpy_s(engine_type, "N/A");
		engine_volume = 0.0;
		max_speed = 0;
	}
	Autotransport(char license_plate[], char brand[], unsigned int release_year, char engine_type[], float engine_volume, int max_speed) {
		strcpy_s(name, "авто");
		strcpy_s(this->license_plate, license_plate);
		strcpy_s(this->brand, brand);
		this->release_year = release_year;
		strcpy_s(this->engine_type, engine_type);
		this->engine_volume = engine_volume;
		this->max_speed = max_speed;
	}
	void SetLicensePlate(char license_plate[]) {
		strcpy_s(this->license_plate, license_plate);
	}
	char* GetLicensePlate() {
		return license_plate;
	}
	void SetBrand(char brand[]) {
		strcpy_s(this->brand, brand);
	}
	char* GetBrand() {
		return brand;
	}
	void SetReleaseYear(unsigned int release_year) {
		this->release_year = release_year;
	}
	unsigned int GetReleaseYear() {
		return release_year;
	}
	void SetEngineType(char engine_type[]) {
		strcpy_s(this->engine_type, engine_type);
	}
	char* GetEngineType() {
		return engine_type;
	}
	void SetEngineVolume(float engine_volume) {
		this->engine_volume = engine_volume;
	}
	float GetEngineVolume() {
		return engine_volume;
	}
	void SetMaxSpeed(int max_speed) {
		this->max_speed = max_speed;
	}
	int GetMaxSpeed() {
		return max_speed;
	}
	virtual ~Autotransport() {}
	virtual AutotransportType getType();
	static void read(list<Autotransport*>& l1, list<Autotransport*>& l2, const char* FILE_NAME);
	static void write(list <Autotransport*>& list_t, char* FILE_NAME);
	virtual void ExportTXT(const char* FILE_NAME);
	virtual char* getString(int number) {
		char nan[4];
		strcpy_s(nan, "N/A");
		return nan;
	}
	virtual int getInt(int number) { return 0; }
	virtual float getFloat(int number) { return 0.0; }
	friend istream& operator>>(istream& s, Autotransport& autotransport);
	friend void InputPositiveNumber(int& number, string msg, int max_value);
	friend void InputPositiveNumber(unsigned int& number, string msg, unsigned int max_value);
	friend void InputPositiveNumber(float& number, string msg, float max_value);
	friend void InputYear(unsigned int& number, string msg);
	static bool brandAscend(Autotransport*& lhs, Autotransport*& rhs);
	static bool brandDescend(Autotransport*& lhs, Autotransport*& rhs);
	static bool YearAscend(Autotransport*& lhs, Autotransport*& rhs);
	static bool YearDescend(Autotransport*& lhs, Autotransport*& rhs);
	static bool engVolAscend(Autotransport*& lhs, Autotransport*& rhs);
	static bool engVolDescend(Autotransport*& lhs, Autotransport*& rhs);
	static bool speedAscend(Autotransport*& lhs, Autotransport*& rhs);
	static bool speedDescend(Autotransport*& lhs, Autotransport*& rhs);
	void Input();
	void Output();
	static int MenuAscOrDescOrder();
};
class Passenger_auto : public Autotransport {
protected:
	char transport_type[13];
	unsigned int passengers_number;
public:
	Passenger_auto() :Autotransport() {
		strcpy_s(transport_type, "N/A");
		passengers_number = 0;
	}
	Passenger_auto(char transport_type[], unsigned int passengers_number) :Autotransport(license_plate, brand, release_year, engine_type, engine_volume, max_speed) {
		strcpy_s(this->transport_type, transport_type);
		this->passengers_number = passengers_number;
	}
	Passenger_auto(char license_plate[], char brand[], unsigned int release_year, char engine_type[], float engine_volume, int max_speed, char transport_type[], unsigned int passengers_number) :Autotransport(license_plate, brand, release_year, engine_type, engine_volume, max_speed) {
		strcpy_s(this->transport_type, transport_type);
		this->passengers_number = passengers_number;
	}
	Passenger_auto(const Passenger_auto& pas) {
		strcpy_s(this->brand, pas.brand);
		strcpy_s(this->license_plate, pas.license_plate);
		strcpy_s(this->engine_type, pas.engine_type);
		strcpy_s(this->transport_type, pas.transport_type);
		this->engine_volume = pas.engine_volume;
		this->release_year = pas.release_year;
		this->max_speed = pas.max_speed;
		this->passengers_number = pas.passengers_number;
	}

	void SetTransportType(char transport_type[]) {
		strcpy_s(this->transport_type, transport_type);
	}
	char* GetTransportType() {
		return transport_type;
	}
	void SetPassengersNumber(unsigned int passengers_number) {
		this->passengers_number = passengers_number;
	}
	unsigned int GetPassengersNumber() {
		return passengers_number;
	}
	void Input();
	void Output();
	char* getString(int number) {
		char nan[4];
		strcpy_s(nan, "N/A");
		switch (number)
		{
		case 1:
			return this->transport_type;
		default:
			return nan;
		}
	}
	int getInt(int number) {
		switch (number)
		{
		case 1:
			return this->passengers_number;
		default:
			return 0;
		}
	}
	friend istream& operator>>(istream& s, Passenger_auto& passeng_auto);
	friend ostream& operator<<(ostream& s, Passenger_auto& passeng_auto);
	static int MenuSearch();
	static void Header();
	static void HeaderTXT(const char* FILE_NAME);
	void ExportTXT(const char* FILE_NAME);
	static void search(list <Autotransport*>& list_t);
	static void sort(list <Autotransport*>& list_t);
	static int MenuSort();
	static bool passeng_numbAscend(Autotransport*& lhs, Autotransport*& rhs);
	static bool passeng_numbDescend(Autotransport*& lhs, Autotransport*& rhs);
};

class Cargo_auto : public Autotransport {
protected:
	char body_type[15];
	float capacity;
public:
	Cargo_auto() :Autotransport() {
		strcpy_s(body_type, "N/A");
		capacity = 0.0;
	}
	Cargo_auto(char body_type[], float capacity) :Autotransport(license_plate, brand, release_year, engine_type, engine_volume, max_speed) {
		strcpy_s(this->body_type, body_type);
		this->capacity = capacity;
	}
	Cargo_auto(const Cargo_auto& carg) {
		strcpy_s(this->brand, carg.brand);
		strcpy_s(this->license_plate, carg.license_plate);
		strcpy_s(this->engine_type, carg.engine_type);
		strcpy_s(this->body_type, carg.body_type);
		this->engine_volume = carg.engine_volume;
		this->release_year = carg.release_year;
		this->max_speed = carg.max_speed;
		this->capacity = carg.capacity;
	}
	void SetBodyType(char body_type[]) {
		strcpy_s(this->body_type, body_type);
	}
	char* GetBodyType() {
		return body_type;
	}
	void SetCapacity(float capacity) {
		this->capacity = capacity;
	}
	float GetCapacity() {
		return capacity;
	}
	void Input();
	void Output();
	void ExportTXT(const char* FILE_NAME);
	static void search(list <Autotransport*>& list_t);
	static void sort(list <Autotransport*>& list_t);
	char* getString(int number) {
		char nan[4];
		strcpy_s(nan, "N/A");
		switch (number)
		{
		case 1:
			return this->body_type;
		default:
			return nan;
		}
	}
	float getFloat(int number) {
		switch (number)
		{
		case 1:
			return this->capacity;
		default:
			return 0;
		}
	}
	static int MenuSearch();
	static int MenuSort();
	static void Header();
	static void HeaderTXT(const char* FILE_NAME);
	static bool capacityAscend(Autotransport*& lhs, Autotransport*& rhs);
	static bool capacityDescend(Autotransport*& lhs, Autotransport*& rhs);
	friend istream& operator>>(istream& s, Cargo_auto& cargo_auto);
	friend ostream& operator<<(ostream& s, Cargo_auto& cargo_auto);
};