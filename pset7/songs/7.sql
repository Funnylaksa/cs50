SELECT
    SUM(energy) / COUNT(energy) as AVERAGE
FROM
    songs
WHERE
    artist_id = (SELECT id FROM artists WHERE name = "Drake")