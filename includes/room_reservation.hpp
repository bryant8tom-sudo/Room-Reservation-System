#ifndef ROOM_RESERVATION_HPP
#define ROOM_RESERVATION_HPP

#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

class RoomReservation {
public:
  RoomReservation(int room_capacity);
  RoomReservation(const std::string& filename, int room_capacity);
  RoomReservation(const RoomReservation& r) = delete;
  ~RoomReservation();
  void AddTeamMember(const std::string& student);
  void RemoveTeamMember(const std::string& student);
  void MoveHotels(int new_room_capacity);
  std::string* GetRoom(int room_number);
  int RoomsReserved() const;
  int RoomCapacity() const;
  int GetOccupantCount(int room_number);
  void Print();
  void Clear();

private:
  std::string** rooms_ = nullptr;
  int rooms_reserved_ = 0;
  int room_capacity_ = 0;
  int athlete_count_ = 0;
};

#endif
