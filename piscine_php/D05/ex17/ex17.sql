SELECT COUNT(DISTINCT id_abo) AS 'nb_abo', TRUNCATE(AVG(prix), 0) AS 'moy_abo', MOD(SUM(duree_abo), 42) AS 'ft' FROM abonnement;
