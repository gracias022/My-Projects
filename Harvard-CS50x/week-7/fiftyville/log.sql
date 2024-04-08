-- Keep a log of any SQL queries you execute as you solve the mystery.

-- list all tables in the database
.tables
-- look at crime scene report
.schema crime_scene_reports
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';
-- DESCRIPTION INFO
-- took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.


-- look at interview
SELECT id, name, transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28;
-- witnesses and their account
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |


-- look at bakery_security_logs
.schema bakery_security_logs
SELECT id, license_plate, hour, minute, activity
FROM bakery_security_logs
WHERE day = 28 AND month = 7
AND year = 2023;

-- bakery (1015-1025)

| 260 | 5P2BI95       | 10   | 16     | exit     |
| 261 | 94KL13X       | 10   | 18     | exit     |
| 262 | 6P58WS2       | 10   | 18     | exit     |
| 263 | 4328GD8       | 10   | 19     | exit     |
| 264 | G412CB7       | 10   | 20     | exit     |
| 265 | L93JTIZ       | 10   | 21     | exit     |
| 266 | 322W7JE       | 10   | 23     | exit     |
| 267 | 0NTHK55       | 10   | 23     | exit     |

SELECT people.id, name, phone_number, passport_number
FROM bakery_security_logs
JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2023
AND hour = 10 AND minute <= 35 AND minute > 15
ORDER BY minute;

-- Possible suspects
|   id   |  name   |  phone_number  | passport_number |
+--------+---------+----------------+-----------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      |
| 243696 | Barry   | (301) 555-4174 | 7526138472      |
| 467400 | Luca    | (389) 555-5198 | 8496433585      |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      |
| 396669 | Iman    | (829) 555-5269 | 7049073643      |
| 514354 | Diana   | (770) 555-1861 | 3592750733      |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      |


-- earliest flight out of fiftyville on 29/7/2023
-- the city the thief escaped to
SELECT city
FROM airports
WHERE id =
(
    SELECT destination_airport_id       -- this nested query gives destination_airport_id = 4
    FROM airports, flights
    WHERE airports.id = flights.origin_airport_id
    AND city = 'Fiftyville'
    AND year = 2023 AND month = 7 AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

+---------------+
|     city      |
+---------------+
| New York City |
+---------------+

--  thief withdrew money from ATM on Leggett Street on morning of 28/7.
SELECT transaction_type, name
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2023 AND month = 7
AND day = 28
AND atm_location = 'Leggett Street';

| transaction_type |  name   |
+------------------+---------+
| withdraw         | Bruce   | -
| deposit          | Kaelyn  |
| withdraw         | Diana   | -
| withdraw         | Brooke  |
| withdraw         | Kenny   |
| withdraw         | Iman    | -
| withdraw         | Luca    | -
| withdraw         | Taylor  |
| withdraw         | Benista |

-- Updated suspect list: Bruce, Diana, Iman, Luca

-- look at flight passengers
    -- check flight id
SELECT id
FROM flights
WHERE year = 2023 AND month = 7
AND day = 29
AND destination_airport_id = 4;

 id |
+----+
| 36 |

    -- check passengers onboard
SELECT name
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36;

|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  | -
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca   | -
+-------

-- Updated suspects: Bruce, Luca
 Bruce   | (367) 555-5533
 Luca    | (389) 555-5198

-- near 10.15 on 28/7, talked to accomplice for <1min
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2023 AND month = 7
AND day = 28
AND duration < 60;

    caller     |    receiver    | duration |
+----------------+----------------+----------+
| (130) 555-0289 | (996) 555-8899 | 51       |
| (499) 555-9472 | (892) 555-8872 | 36       |
| (367) 555-5533 | (375) 555-8161 | 45       | -- bruce is the culprit
| (499) 555-9472 | (717) 555-1342 | 50       |
| (286) 555-6063 | (676) 555-6554 | 43       |
| (770) 555-1861 | (725) 555-3243 | 49       |
| (031) 555-6622 | (910) 555-3251 | 38       |
| (826) 555-1652 | (066) 555-9701 | 55       |
| (338) 555-6650 | (704) 555-2131 | 54

-- Accomplice's phone number: (375) 555-8161
-- Accomplice's identity:
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';

+-------+
| name  |
+-------+
| Robin |
+-------+
