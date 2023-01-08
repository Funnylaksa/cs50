-- SELECT
--     *
-- FROM
--     people
-- WHERE
--     license_plate IN (
--         SELECT
--             license_plate
--         FROM
--             bakery_security_logs
--         WHERE
--             month = 7
--             AND day = 28
--             AND hour = 10
--             AND activity = "exit"
--     )
--     AND id IN (
--         SELECT
--             id
--         FROM
--             people
--         WHERE
--             id IN (
--                 SELECT
--                     person_id
--                 FROM
--                     bank_accounts
--                 WHERE
--                     account_number IN (
--                         SELECT
--                             account_number
--                         FROM
--                             atm_transactions
--                         WHERE
--                             month = 7
--                             AND day = 28
--                             AND atm_location = "Leggett Street"
--                     )
--             )
--     )
--     AND passport_number IN (
--         SELECT
--             passport_number
--         FROM
--             passengers
--         WHERE
--             flight_id IN (
--                 SELECT
--                     id
--                 FROM
--                     flights
--                 WHERE
--                     month = 7
--                     AND day = 29
--             )
--     )



SELECT
    caller,
    receiver,
    p1.name,
    p2.name,
    duration
FROM
    phone_calls
    JOIN people p1 ON p1.phone_number = phone_calls.caller
    JOIN people p2 ON p2.phone_number = phone_calls.receiver
WHERE
    month = 7
    AND day = 28
    AND duration < 60
    AND p1.name IN (
        SELECT
            name
        FROM
            people
        WHERE
            license_plate IN (
                SELECT
                    license_plate
                FROM
                    bakery_security_logs
                WHERE
                    month = 7
                    AND day = 28
                    AND hour = 10
                    AND activity = "exit"
                    AND minute >= 15
                    AND minute <= 25
                    AND year = 2021
            )
            AND id IN (
                SELECT
                    id
                FROM
                    people
                WHERE
                    id IN (
                        SELECT
                            person_id
                        FROM
                            bank_accounts
                        WHERE
                            account_number IN (
                                SELECT
                                    account_number
                                FROM
                                    atm_transactions
                                WHERE
                                    month = 7
                                    AND day = 28
                                    AND atm_location = "Leggett Street"
                            )
                    )
            )
            AND passport_number IN (
                SELECT
                    passport_number
                FROM
                    passengers
                WHERE
                    flight_id IN (
                        SELECT
                            id
                        FROM
                            flights
                        WHERE
                            month = 7
                            AND day = 29
                    )
            )
    )


-- SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number = 47746428)
-- (367) 555-5533|(375) 555-8161|Bruce|Robin|45
-- (286) 555-6063|(676) 555-6554|Taylor|James|43
-- (770) 555-1861|(725) 555-3243|Diana|Philip|49


-- SELECT * FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE name IN ("Bruce", "Robin"))