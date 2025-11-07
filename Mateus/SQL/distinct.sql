SELECT DISTINCT marca 
FROM carro ca 
JOIN cliente cli ON ca.nif=cli.nif
WHERE ca.nif = 1232;

