#include "room_reservation.hpp"


void RoomReservation::AddTeamMember(const std::string& student) {
  if (rooms_reserved_ == 0 || GetOccupantCount(rooms_reserved_ - 1) == room_capacity_) {
    std::string** new_rooms = new std::string**[rooms_reserved_ + 1];
    for (int i = 0; i < rooms_reserved_; i++) {
      new_rooms[i] == rooms_[i];
    }
    new_rooms[rooms_reserved_] = new std::string[room_capacity_];
    if (rooms_ != nullptr) {
      delete[] rooms_;
    }
    rooms_ = new_rooms;
    rooms_resesrved_++;
  }
  rooms_[rooms_reserved_ - 1][GetOccupantCount(rooms_reserved_ - 1)] = student;
  athlete_count_++;
}
void RoomReservation::RemoveTeamMember(const std::string& student) {
  int bed = -1;
  int room = -1;
  for (int i = 0; i < rooms_reserved_; i++) {
    int room_count_ = GetOccupantCount(i);
    for (int j = 0; j < room_count_; j++) {
      if (rooms_[i][j] == student) {
        bed = j;
        room = i;
        break;
      }
    }
    if (room != -1) {
      break;
    }
  }
  if (room == -1) {
        throw std::invalid_argument("Student not found.");
    }

    rooms_[room][bed] = "";

    int curr_r = room;
    int curr_b = bed;

    while (true) {
        int next_r = curr_r;
        int next_b = curr_b + 1;

        if (next_b == room_capacity_) {
            next_r++;
            next_b = 0;
        }

        if (next_r >= rooms_reserved_ || rooms_[next_r][next_b] == "") {
            break;
        }

        std::swap(rooms_[curr_r][curr_b], rooms_[next_r][next_b]);
        
        curr_r = next_r;
        curr_b = next_b;
    }

    if (GetOccupantCount(rooms_reserved_ - 1) == 0) {
        // Deallocate the memory for the last room array
        delete[] rooms_[rooms_reserved_ - 1];
        rooms_reserved_--;

        if (rooms_reserved_ == 0) {
            delete[] rooms_;
            rooms_ = nullptr;
        }
    }
    athlete_count_--;
}
void RoomReservation::MoveHotels(int new_room_capacity) {
  int new_rooms_reserved = 0;
    if (athlete_count_ > 0) {
        new_rooms_reserved = static_cast<int>(std::ceil(static_cast<double>(athlete_count_) / new_room_capacity));
    }

    std::string** new_rooms = nullptr;
    
    if (new_rooms_reserved > 0) {
        new_rooms = new std::string*[new_rooms_reserved];
        
        for (int i = 0; i < new_rooms_reserved; ++i) {
            new_rooms[i] = new std::string[new_room_capacity];
        }
    }

    int current_new_room = 0;
    int current_new_bed = 0;

    for (int r = 0; r < rooms_reserved_; ++r) {
        int occupants = GetOccupantCount(r);
        for (int b = 0; b < occupants; ++b) {
            new_rooms[current_new_room][current_new_bed] = rooms_[r][b];
            
            current_new_bed++;

            if (current_new_bed == new_room_capacity) {
                current_new_room++;
                current_new_bed = 0;
            }
        }
    }

    if (rooms_ != nullptr) {
        for (int r = 0; r < rooms_reserved_; ++r) {
            delete[] rooms_[r]; 
        }
        delete[] rooms_; 
    }

    rooms_ = new_rooms;
    room_capacity_ = new_room_capacity;
    rooms_reserved_ = new_rooms_reserved;
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
