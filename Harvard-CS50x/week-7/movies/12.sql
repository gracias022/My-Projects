-- list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
SELECT title
FROM movies, stars, people
WHERE movies.id = stars.movie_id
AND stars.person_id = people.id
AND name = 'Bradley Cooper'
AND title IN
(
    SELECT title
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE name = 'Jennifer Lawrence'
);
