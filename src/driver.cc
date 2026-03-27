#include <iostream>

#include "room_reservation.hpp"

int main() {

  std::cout << "\nAdd all student athletes from file into a hotel with a room capacity of 2:" << std::endl;
  RoomReservation tennis_team("sample/womens_tennis.txt", 2);
  tennis_team.Print();

  std::cout << "\nRemove an athlete from the hotel:" << std::endl;
  tennis_team.RemoveTeamMember("Kida Ferrari");
  tennis_team.Print();

  std::cout << "\nRemove another athlete from the hotel, unreserve a room:" << std::endl;
  tennis_team.RemoveTeamMember("Rosie Seccia");
  tennis_team.Print();

  std::cout << "\nMove to a new hotel with a room capacity of 5:" << std::endl;
  tennis_team.MoveHotels(5);
  tennis_team.Print();

  std::cout << "\nMove back to the original hotel with room capacity 2:" << std::endl;
  tennis_team.MoveHotels(2);
  tennis_team.Print();

  return 0;
}
