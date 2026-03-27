#define CATCH_CONFIG_MAIN
#include <fstream>
#include <sstream>
#include <string>

#include "catch.hpp"
#include "room_reservation.hpp"

TEST_CASE("RoomReservation::AddTeamMember() Add a single team member",
          "[AddTeamMember()_case_1]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");

  REQUIRE(rr.GetRoom(0) != nullptr);
  REQUIRE(rr.GetOccupantCount(0) == 1);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");

  REQUIRE(rr.GetRoom(0)[1].empty());
  REQUIRE(rr.GetRoom(0)[2].empty());
}

TEST_CASE(
    "RoomReservation::AddTeamMember() There exists a reserved room with space "
    "for a student",
    "[AddTeamMember()_case_2]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");
  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");

  rr.AddTeamMember("Alice Xu");

  REQUIRE(rr.GetOccupantCount(0) == 3);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");
  REQUIRE(rr.GetRoom(0)[2] == "Ariel Madatali");

  REQUIRE(rr.GetOccupantCount(1) == 3);
  REQUIRE(rr.GetRoom(1)[0] == "Violeta Martinez");
  REQUIRE(rr.GetRoom(1)[1] == "Rosie Seccia");
  REQUIRE(rr.GetRoom(1)[2] == "Alice Xu");

  REQUIRE(rr.GetRoom(2) == nullptr);
}

TEST_CASE("RoomReservation::AddTeamMember() All rooms are currently full",
          "[AddTeamMember()_case_3]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");

  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");

  rr.AddTeamMember("Kasia Treiber");

  REQUIRE(rr.GetOccupantCount(0) == 3);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");
  REQUIRE(rr.GetRoom(0)[2] == "Ariel Madatali");

  REQUIRE(rr.GetOccupantCount(1) == 3);
  REQUIRE(rr.GetRoom(1)[0] == "Violeta Martinez");
  REQUIRE(rr.GetRoom(1)[1] == "Rosie Seccia");
  REQUIRE(rr.GetRoom(1)[2] == "Alice Xu");

  REQUIRE(rr.GetOccupantCount(2) == 1);
  REQUIRE(rr.GetRoom(2)[0] == "Kasia Treiber");

  REQUIRE(rr.GetRoom(3) == nullptr);
}
TEST_CASE("RoomReservation::RemoveTeamMember() Delete from room, room array",
          "[RemoveTeamMember()_case_1]") {
  RoomReservation rr("", 3);

  rr.AddTeamMember("Kida Ferrari");
  rr.RemoveTeamMember("Kida Ferrari");
  REQUIRE(rr.GetRoom(0) == nullptr);
}
TEST_CASE("RoomReservation::RemoveTeamMember() Delete from room",
          "[RemoveTeamMember()_case_2]") {
  RoomReservation rr("", 3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");

  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");

  rr.RemoveTeamMember("Alice Xu");

  REQUIRE(rr.GetOccupantCount(0) == 3);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");
  REQUIRE(rr.GetRoom(0)[2] == "Ariel Madatali");

  REQUIRE(rr.GetOccupantCount(1) == 2);
  REQUIRE(rr.GetRoom(1)[0] == "Violeta Martinez");
  REQUIRE(rr.GetRoom(1)[1] == "Rosie Seccia");

  REQUIRE(rr.GetRoom(1) != nullptr);
}

TEST_CASE("RoomReservation::RemoveTeamMember() Delete from room, remove a room",
          "[RemoveTeamMember()_case_3]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");

  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");

  rr.AddTeamMember("Kasia Treiber");

  rr.RemoveTeamMember("Kasia Treiber");

  REQUIRE(rr.GetOccupantCount(0) == 3);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");
  REQUIRE(rr.GetRoom(0)[2] == "Ariel Madatali");

  REQUIRE(rr.GetOccupantCount(1) == 3);
  REQUIRE(rr.GetRoom(1)[0] == "Violeta Martinez");
  REQUIRE(rr.GetRoom(1)[1] == "Rosie Seccia");
  REQUIRE(rr.GetRoom(1)[2] == "Alice Xu");

  REQUIRE(rr.GetRoom(2) == nullptr);
}

TEST_CASE(
    "RoomReservation::RemoveTeamMember() Delete from room, rebalance rooms",
    "[RemoveTeamMember()_case_4]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");

  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");

  rr.AddTeamMember("Kasia Treiber");
  rr.AddTeamMember("Mckenna Schaef");

  rr.RemoveTeamMember("Rosie Seccia");

  REQUIRE(rr.GetOccupantCount(0) == 3);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");
  REQUIRE(rr.GetRoom(0)[2] == "Ariel Madatali");

  REQUIRE(rr.GetOccupantCount(1) == 3);
  REQUIRE(rr.GetRoom(1)[0] == "Violeta Martinez");
  REQUIRE(rr.GetRoom(1)[1] == "Alice Xu");
  REQUIRE(rr.GetRoom(1)[2] == "Kasia Treiber");

  REQUIRE(rr.GetOccupantCount(2) == 1);
  REQUIRE(rr.GetRoom(2)[0] == "Mckenna Schaef");

  REQUIRE(rr.GetRoom(3) == nullptr);
}

TEST_CASE(
    "RoomReservation::MoveHotels() Move hotels resize (complete capacity)",
    "[MoveHotels()_case_1]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");

  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");

  rr.MoveHotels(2);

  REQUIRE(rr.GetOccupantCount(0) == 2);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");

  REQUIRE(rr.GetOccupantCount(1) == 2);
  REQUIRE(rr.GetRoom(1)[0] == "Ariel Madatali");
  REQUIRE(rr.GetRoom(1)[1] == "Violeta Martinez");

  REQUIRE(rr.GetOccupantCount(2) == 2);
  REQUIRE(rr.GetRoom(2)[0] == "Rosie Seccia");
  REQUIRE(rr.GetRoom(2)[1] == "Alice Xu");

  REQUIRE(rr.GetRoom(3) == nullptr);
}

TEST_CASE("RoomReservation::MoveHotels() Move hotels resize (partial capacity)",
          "[MoveHotels()_case_2]") {
  RoomReservation rr(3);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");

  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");

  rr.AddTeamMember("Kasia Treiber");

  rr.MoveHotels(2);

  REQUIRE(rr.GetOccupantCount(0) == 2);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");

  REQUIRE(rr.GetOccupantCount(1) == 2);
  REQUIRE(rr.GetRoom(1)[0] == "Ariel Madatali");
  REQUIRE(rr.GetRoom(1)[1] == "Violeta Martinez");

  REQUIRE(rr.GetOccupantCount(2) == 2);
  REQUIRE(rr.GetRoom(2)[0] == "Rosie Seccia");
  REQUIRE(rr.GetRoom(2)[1] == "Alice Xu");

  REQUIRE(rr.GetOccupantCount(3) == 1);
  REQUIRE(rr.GetRoom(3)[0] == "Kasia Treiber");

  REQUIRE(rr.GetRoom(4) == nullptr);
}
TEST_CASE(
    "RoomReservation::MoveHotels() Move hotels resize (increase capacity)",
    "[MoveHotels()_case_3]") {
  RoomReservation rr(2);

  rr.AddTeamMember("Kida Ferrari");
  rr.AddTeamMember("Megan Heuser");
  rr.AddTeamMember("Ariel Madatali");
  rr.AddTeamMember("Violeta Martinez");
  rr.AddTeamMember("Rosie Seccia");
  rr.AddTeamMember("Alice Xu");
  rr.AddTeamMember("Kasia Treiber");

  rr.MoveHotels(4);

  REQUIRE(rr.GetOccupantCount(0) == 4);
  REQUIRE(rr.GetRoom(0)[0] == "Kida Ferrari");
  REQUIRE(rr.GetRoom(0)[1] == "Megan Heuser");
  REQUIRE(rr.GetRoom(0)[2] == "Ariel Madatali");
  REQUIRE(rr.GetRoom(0)[3] == "Violeta Martinez");

  REQUIRE(rr.GetOccupantCount(1) == 3);
  REQUIRE(rr.GetRoom(1)[0] == "Rosie Seccia");
  REQUIRE(rr.GetRoom(1)[1] == "Alice Xu");
  REQUIRE(rr.GetRoom(1)[2] == "Kasia Treiber");
  REQUIRE(rr.GetRoom(2) == nullptr);
  REQUIRE(rr.GetRoom(3) == nullptr);
}