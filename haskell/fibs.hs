-- linear Fibonacci

fibs :: Int -> Int
fibs = 0 : 1 : ( zipWith (+) fibs (tail fibs))
