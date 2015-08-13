local blob = require('libblob_finder')

local param = {
   minThreshold = 10,
   maxThreshold = 200,
   filterByArea = true,
   minArea = 1500,
   filterByCircularity = true,
   minCircularity = 0.1,
   filterByConvexity = true,
   minConvexity = 0.87,
   filterByInertia = true,
   minInertiaRatio = 0.01,
}

blob.find(param)
