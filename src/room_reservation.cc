#include "room_reservation.hpp"


void RoomReservation::AddTeamMember(const std::string& student) {
  // TODO
}
void RoomReservation::RemoveTeamMember(const std::string& student) {
  // TODO
}
void RoomReservation::MoveHotels(int new_room_capacity) {
  // TODO
}

// DO NOT MODIFY
RoomReservation::RoomReservation(int room_capacity):
    room_capacity_(room_capacity) {}
RoomReservation::RoomReservation(const std::string& filename,
                                 int room_capacity):
    room_capacity_(room_capacity) {
  std::ifstream ifs(filename);
  std::string student;
  while (ifs >> std::quoted(student)) {
    std::cout << student << std::endl;
    AddTeamMember(student);
  }
}
RoomReservation::~RoomReservation() {
  Clear();
}

int RoomReservation::RoomsReserved() const {
  return rooms_reserved_;
}
int RoomReservation::RoomCapacity() const {
  return room_capacity_;
}

void RoomReservation::Clear() {
  if (rooms_ == nullptr) return;
  for (int i = 0; i < rooms_reserved_; i++) {
    delete[] rooms_[i];
  }
  delete[] rooms_;
  rooms_ = nullptr;
  rooms_reserved_ = 0;
  athlete_count_ = 0;
}


std::string* RoomReservation::GetRoom(int room_number) {
  if (room_number < 0 || room_number >= rooms_reserved_ || rooms_ == nullptr) {
    return nullptr;
  }
  return rooms_[room_number];
}
int RoomReservation::GetOccupantCount(int room_number) {
  std::string* room = GetRoom(room_number);
  if (room == nullptr) {
    return 0;
  }
  int occupants = 0;
  for (int i = 0; i < room_capacity_; ++i) {
    if (room[i] != "") occupants++;
  }
  return occupants;
}

void RoomReservation::Print() {
  for (int i = 0; i < rooms_reserved_; ++i) {
    std::cout << "----------------\n";
    std::cout << "Room " << i << std::endl;
    for (int j = 0; j < room_capacity_; ++j) {
      std::string name = (rooms_[i][j] == "") ? "xxxxxxxxx" : rooms_[i][j];
      std::cout << name << '\n';
    }
    std::cout << "----------------\n";
  }
}