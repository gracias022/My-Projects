-- average energy of songs by Drake

-- method 1: JOIN
SELECT AVG(energy)
FROM songs
JOIN artists ON songs.artist_id = artists.id
WHERE artists.name = 'Drake';


-- method 2
-- SELECT AVG(energy)
-- FROM songs
-- WHERE artist_id =
-- (
    -- SELECT id
    -- FROM artists
    -- WHERE name = 'DRAKE';
-- );
