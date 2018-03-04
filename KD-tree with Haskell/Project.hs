-- class Enumerable a 
--     where getValue :: Ord b => a -> Int -> b
import Data.List (sortBy, minimumBy)
import Data.Ord (comparing)

data Point = Point [Double]
  deriving (Eq, Ord, Show, Read)
  -- deriving (Eq, Ord, Enumerable, Show, Read)

-- instance Ord Point where
--     compare p1 p2
--         = compare (calcDistance p1 zeroPoint) (calcDistance p2 zeroPoint)
--         where zeroPoint = (Point (map (\x -> 0) l1))
    

getLength :: Point -> Int
getLength (Point l) = length l
-- _length = 3;
_maxSize = 2;

getValue :: Point -> Int -> Double
getValue (Point fileds) i = fileds !! i

data Node = Node { level::Int, separator::Double, minVal :: Double, maxVal :: Double, 
                    left::Node, right::Node } 
    | Leaf { level::Int, value::[Point] }
           deriving (Eq, Show, Read)

getMediana :: [Point] -> Int -> Double
getMediana l index 
    | (even len) = ((getValue (sorted !! medIndex) index) 
            + (getValue (sorted !! (medIndex - 1)) index)) / 2
    | otherwise = (getValue (sorted !! medIndex) index)
    where 
        sorted = sortBy (comparing (\e -> (getValue e index))) l
        len = length l
        medIndex = div len 2

getAverage :: [Point] -> Int -> Double
getAverage points index 
    = (sum [(getValue x index) | x<-points]) / (fromIntegral (length points))

getSeparator :: [Point] -> Int -> Double
getSeparator points index = getAverage points index

getMin :: [Point] -> Int -> Double
getMin [x] index = getValue x index
getMin (x:xs) index = min
    where 
        currentVal = (getValue x index)
        afterMin = getMin xs index
        min = if currentVal < afterMin then currentVal else afterMin

getMax :: [Point] -> Int -> Double
getMax [x] index = getValue x index
getMax (x:xs) index = max
    where 
        currentVal = (getValue x index)
        afterMax = getMax xs index
        max = if currentVal > afterMax then currentVal else afterMax

subBuild :: [Point] -> Int -> Node
subBuild points level
    | _maxSize < (length points) -- && (length left) /= 0 && (length right) /= 0
        = Node level sep minVal maxVal (subBuild left nextLevel) (subBuild right nextLevel)
    | otherwise = Leaf level points
    where 
        len = getLength (points !! 0)
        index = rem level len
        sep = getSeparator points index
        left = [p | p<-points, (getValue p index) < sep]
        right = [p | p<-points, (getValue p index) >= sep]
        minVal = getMin points index
        maxVal = getMax points index
        -- nextIndex = rem index len
        nextLevel = level + 1

buildTree :: [Point] -> Node
buildTree points = subBuild (removeDublicates points) 0

data Interval = Interval [(Double, Double)]

belong :: Point -> Int -> Double -> Double -> Bool
belong point index start end = start <= val && val <= end
    where val = getValue point index

removeDublicates :: Eq a => [a] -> [a]
removeDublicates [x] = [x]
removeDublicates (x:xs) 
    | elem x result = result
    | otherwise = (x:result)
    where result = removeDublicates xs

myFilter :: [Point] -> Interval -> [Point] 
myFilter [] _ = []
myFilter l (Interval []) = l
myFilter l (Interval intv)
    = myFilter (filter (\p -> belong p index start end) l) (Interval (tail intv))
    where
        len = getLength (head l)
        index = (len - (length intv))
        start = fst (head intv)
        end = snd (head intv)


searchInterval :: Node -> Interval -> [Point]
searchInterval (Leaf _ []) _ = []
searchInterval (Leaf lvl points) (Interval intv) 
    -- = filter (\p -> (belong p index start end)) points
    = myFilter points (Interval intv)
    where 
        len = length intv
        index = rem lvl len
        start = fst (intv !! index)
        end = snd (intv !! index)

searchInterval (Node lvl sep minVal maxVal left right) (Interval intv) 
    | start < maxVal && end > minVal && start <= sep && sep <= end
        = (searchInterval left (Interval intv)) ++ (searchInterval right (Interval intv))
    | start < maxVal && end > minVal && end <=  sep
        = (searchInterval left (Interval intv))
    | start < maxVal && end > minVal && sep <= start
        = (searchInterval right (Interval intv))
    -- | start <= maxVal && end >= minVal
    --     = (searchInterval left (Interval intv)) ++ (searchInterval right (Interval intv))
    | otherwise = []
    where 
        len = length intv
        index = rem lvl len
        start = fst (intv !! index)
        end = snd (intv !! index)

calcDistance :: Point -> Point -> Double
calcDistance (Point l1) (Point l2) = sqrt (sum (map (^2) ziped))
    where ziped = (zipWith (\x y -> x - y) l1 l2)

mostClose :: [Point] -> Point -> Point
mostClose [x] point = x
mostClose (x:xs) point 
    | distCp < currentDist = clostPoint
    | otherwise = x
    where 
        clostPoint = mostClose xs point
        distCp = calcDistance clostPoint point
        currentDist = calcDistance x point

searchNeighbor :: Node -> Point -> Point
searchNeighbor (Leaf lvl points) point = mostClose points point 
searchNeighbor (Node lvl sep minVal maxVal left right) point
    | (value - sep) >= 0 = searchNeighbor right point
    | otherwise = searchNeighbor left point
    where 
        len = getLength point
        index = rem lvl len
        value = getValue point index

-- t = [Point [1,2,3],
--     Point [5,2,3],
--     Point [3,2,3], 
--     Point [15,2,3],
--     Point [1,3,3],
--     Point [2,2,7], 
--     Point [3,15,3],
--     Point [7,9,3],
--     Point [5,3,2],
--     Point [3,7,3], 
--     Point [3,5,3]]

t2 = [Point [2,3],
    Point [3,3],
    Point [2,7], 
    Point [15,3],
    Point [9,3],
    Point [15,2],
    Point [3,2],
    Point [7,3], 
    Point [5,3]]

main = do {
    -- print (sortBy (comparing (\e -> (getValue e 0))) t);
    -- print (getMediana t 0);
    -- print (getMin t 0);
    -- print (getMax t 0);
    -- print (minimumBy (\(Point (x,y,z)) -> x) t);
    -- print (sortBy (comparing (\e -> (getValue e 0))) t);
    -- print (buildTree t)
    -- print (buildTree t2);
    print (searchInterval (buildTree t2) (Interval [(1,5), (1,3)]));
    print (searchNeighbor (buildTree t2) (Point [13,12]));
    -- print (myFilter t2 (Interval [(1,3),(1,3)]));
    -- print ();
    -- print (t !! 1);
    -- print (getLength (t !! 0));
    -- print (Point (t !! 1));
    -- print (length (t !! 1));
}







