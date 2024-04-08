-- ilst names of songs that feature other artists (i.e. "feat." in song name)
SELECT name
FROM songs
where name LIKE '%feat.%';
