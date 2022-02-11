#!/usr/bin/env python

                        # Creates a fake dataset for 100,000 users and exports it to a CSV file
                                    # For ML and data science practice 

import pandas as pd
import uuid
import random
from faker import Faker
import datetime

# Initalizes the Faker library
faker = Faker()

# Creates the 100,000 users
num_users= 100000

# The different metrics that are used in tracking and measuring data
features= {
    "ID",
    "Gender",
    "Subscriber",
    "Name",
    "DoB",
    "Education",
    "Rating"
} 

# Creating a datafield for these features
df = pd.DataFrame(columns=features)

# Attaches an ID to each user (low chance for a repeated ID)
df['ID']= [uuid.uuid4().hex for i in range(num_users)]

# Generates fake names, ensuring that the names match the gender
def name_gen(gender):
    if gender == 'male':
        return faker.name_male()
    elif gender == 'female':
        return faker.name_female()
    return faker.name()

# Creates different genders and gives each a different probability of occuring
genders = ["male", "female", "other"]

df['Gender'] = random.choices(
    genders,
    weights=(49, 45, 6),
    k=num_users
)

df['Name'] = [name_gen(i) for i in df['Gender']]

# Randomly disbributing the chance that a user is a subscriber or not
choice= [True, False]

df['Subscriber']= random.choices(
    choice,
    k=num_users
)

# Generates a list of Dates of Birth ranging from 1960 - 2005 in 'DD-MM-YYYY' format
def random_dob(start, end, n):

    frmt = "%Y-%m-%d"

    stime= datetime.datetime.strptime(start, frmt)
    etime= datetime.datetime.strptime(end, frmt)

    td= etime - stime

    times= [(random.random() * td + stime).strftime(frmt) for _ in range(n)]

    return times

df['DoB'] = random_dob("1960-01-01", "2005-01-01", num_users)

# Assigns an education level depending on age 
def get_education(dob):
    
    now= datetime.datetime.now()
    dob= datetime.datetime.strptime(dob, "%Y-%m-%d")

    age= int((now - dob).days/365.25)

    if age <= 18:
        return 'High Schoool'
    elif age <= 22:
        return 'Undergrad'
    elif age <= 25:
        return 'Grad'
    else:
        return 'Employed'

df['Education']= [get_education(i) for i in df['DoB']]

# Assings different ratings to each user, each rating having a different probability of happening
ratings= [1, 2, 3, 4, 5]

df['Rating']= random.choices(
    ratings,
    weights=(25, 15, 15, 20, 25),
    k= num_users
)

df.to_csv('consumer_data.csv')