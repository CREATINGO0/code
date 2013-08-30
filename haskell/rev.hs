rev [] = []
-- rev xs = last xs : rev (init xs)
-- rev xs = rev (tail xs) ++ [head xs]
rev (x:xs) = reverse xs ++ [x]
