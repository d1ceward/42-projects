SELECT film.titre AS `Titre`, film.resum AS `Resume`, film.annee_prod FROM film INNER JOIN genre ON film.id_genre = genre.id_genre WHERE genre.nom = 'erotic' ORDER BY film.annee_prod DESC;
