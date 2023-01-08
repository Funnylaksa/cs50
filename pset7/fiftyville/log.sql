-- Keep a log of any SQL queries you execute as you solve the mystery.
-- SELECT * FROM crime_scene_reports LIMIT 5
-- SELECT * FROM interviews 
-- SELECT * FROM atm_transactions LIMIT 5
-- SELECT * FROM bank_accounts LIMIT 5
-- SELECT * FROM airports LIMIT 5
-- SELECT * FROM flights LIMIT 5
-- SELECT * FROM passengers LIMIT 5
-- SELECT * FROM phone_calls
-- SELECT * FROM people
-- SELECT * FROM bakery_security_logs


-- ? Start
-- SELECT * from crime_scene_reports WHERE month = 7 AND day = 28 and street = "Humphrey Street"
-- 10.15am 28 July Humphrey Street
-- 3 witnesses

-- ? Interview logs from 3 person 
-- SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28
-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- thief withdraw money
-- thief + accomplice flight 29 July
-- accomplice buy flight ticket 28/29 july

-- SELECT * FROM phone_calls WHERE month = 7 AND day = 28

-- ? Car exiting crime scene 28July 10+ am
-- SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit"

-- Persons with cars exiting crime scene 
-- SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit")
-- 221103|Vanessa|(725) 555-4692|2963008352|5P2BI95
-- 243696|Barry|(301) 555-4174|7526138472|6P58WS2
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street"
-- 246|28500762|2021|7|28|Leggett Street|withdraw|48
-- 264|28296815|2021|7|28|Leggett Street|withdraw|20
-- 266|76054385|2021|7|28|Leggett Street|withdraw|60
-- 267|49610011|2021|7|28|Leggett Street|withdraw|50
-- 269|16153065|2021|7|28|Leggett Street|withdraw|80
-- 275|86363979|2021|7|28|Leggett Street|deposit|10
-- 288|25506511|2021|7|28|Leggett Street|withdraw|20
-- 313|81061156|2021|7|28|Leggett Street|withdraw|30
-- 336|26013199|2021|7|28|Leggett Street|withdraw|35

-- SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street"))
-- 395717|Kenny|(826) 555-1652|9878712108|30G67EN
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 438727|Benista|(338) 555-6650|9586786673|8X428L0
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 458378|Brooke|(122) 555-4581|4408372428|QX4YZN3
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X
-- 948985|Kaelyn|(098) 555-1164|8304650265|I449449


-- Car exiting and withdrawing money at Leggett Street
-- SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit") AND id IN 
-- (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street")))
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X


-- SELECT * FROM passengers LIMIT 5


-- ? passengers taking flights flying on 29July
-- SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29)


-- ? passengers flying on 29 July withdrawing at Leggett street and have cars 
SELECT * FROM people WHERE 
    license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit") 
AND id IN (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street")))
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29))
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- SELECT * FROM bank_accounts LIMIT 5