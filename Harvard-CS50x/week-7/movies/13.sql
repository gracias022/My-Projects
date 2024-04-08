-- list the names of all people who starred in a movie in which Kevin Bacon (born in 1958) also starred.
SELECT name
FROM people, stars, movies
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND movies.id IN
(
    SELECT movies.id
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE name = 'Kevin Bacon' AND birth = 1958
)
AND name != 'Kevin Bacon';
