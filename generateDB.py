#!/usr/bin/env python

from faker import Faker
import random
from datetime import datetime

faker = Faker()

def IDName(f, l):
	return (l.lower() + f.lower())

test_network = open("test_network.db","w")
names = {}
names_arr = []
for x in range(1000):
	name = faker.name()
	names[name] = []
	names_arr.append(name)

for x in names:
	random.seed(datetime.now())
	num_friends = random.randint(1, (len(names_arr) / 2))
	x_arr = x.split(" ")
	x_fname = x_arr[0]
	if x_fname == "Mr." or x_fname == "Dr." or x_fname == "Mrs." or x_fname == "Ms." or x_fname == "Miss":
		x_fname = "John"
	x_lname = x_arr[1]
	x_id = IDName(x_fname, x_lname)
	for y in range(num_friends):
		random.seed(datetime.now())
		friend_num = random.randint(0, len(names_arr) - 1)
		friend = names_arr[friend_num]
		friend_arr = friend.split(" ")
		friend_fname = friend_arr[0]
		if friend_fname == "Mr." or friend_fname == "Dr." or friend_fname == "Mrs." or friend_fname == "Ms." or friend_fname == "Miss":
			friend_fname = "John"
		friend_lname = friend_arr[1]
		friend_id = IDName(friend_fname, friend_lname)
		if not friend_id in names[x] and friend_id != x_id:
			names[x].append(friend_id)
			names[friend].append(x_id)

for x in names:
	full_name = x
	full_name_arr = full_name.split(" ")
	first_name = full_name_arr[0]
	if first_name == "Mr." or first_name == "Dr." or first_name == "Mrs." or first_name == "Ms." or first_name == "Miss":
		first_name = "John"
	last_name = full_name_arr[1]
	id_name = IDName(first_name, last_name)

	test_network.write(last_name + ", " + first_name + "\n")

	random.seed(datetime.now())
	day = random.randint(1,28)
	month = random.randint(1,12)
	year = random.randint(1900,2019)
	test_network.write(str(month) + "/" + str(day) + "/" + str(year) + "\n")

	test_network.write("(personal) " + id_name + "@yahoo.com" + "\n")
	test_network.write("(cell) " + "412680" + str(year) + "\n")

	for y in names[x]:
		test_network.write(y + "\n")

	test_network.write("------------------------------\n")


test_network.close();