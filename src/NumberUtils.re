/* module.exports = function (weights) {
   	var totalWeight = 0,
   		i, random;

   	for (i = 0; i < weights.length; i++) {
   		totalWeight += weights[i];
   	}

   	random = Math.random() * totalWeight;

   	for (i = 0; i < weights.length; i++) {
   		if (random < weights[i]) {
   			return i;
   		}

   		random -= weights[i];
   	}

   	return -1;
   }; */

let sum = (a, b) => a +. b;

let calculateWeights = (accumulator, weight) => {
  let (random, counter, default) = accumulator;
  switch (random, default) {
  | (r, result) when result !== (-1) => (r, counter, result)
  | (r, _) when r < weight => (r, counter, counter)
  | (r, _) => (r -. weight, counter + 1, default)
  };
};

let getRandomWeight = (weights, random) => {
  let totalWeight = ArrayLabels.fold_left(~init=0.0, ~f=sum, weights);
  let t = (random *. totalWeight, 0, (-1));
  let randomWeight =
    ArrayLabels.fold_left(~init=t, ~f=calculateWeights, weights);
  let (_, _, result) = randomWeight;
  result;
};