-- list the names of all people who have directed a movie
-- that received a rating of at least 9.0.
SELECT DISTINCT name
FROM directors, people, movies, ratings
WHERE directors.person_id = people.id
AND directors.movie_id = movies.id
AND movies.id = ratings.movie_id
AND rating >= 9.0;
