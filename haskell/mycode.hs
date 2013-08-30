-- mycode.hs
-- | the 'aipTogether' function binds together two lists

zipTogether :: [a] -> [b] -> [(a,b)]
zipTogether [] [] = []
zipTogether [] ys = []
zipTogether xs [] = []
zipTogether (x:xs) (y:ys) = (x,y) : zipTogether xs ys
