class Age:
    """Define methods to get fuzzy values of given age in three sets i.e. young, middle, and old."""

    def __int__(self):
        pass

    def young(self, age):
        """Get value for young fuzzy set for given age."""
        if age < 20.0:
            return 1.0
        elif 20.0 <= age < 35.0:
            return float((35-age)/15.0)
        else:
            return 0.0
        
    def middle(self, age):
        """Get value for middle fuzzy set for given age."""
        if age <= 20 or age > 60:
            return 0.0
        elif 20 < age <= 35:
            return float(age-20)/15
        elif 35 < age <= 45:
            return 1.0
        elif 45 < age <= 60:
            return (60-age)/15.0
        
    def old(self, age):
        """get value for old fuzzy set for given age."""
        if age <= 45:
            return 0.0
        elif 45 < age <= 60:
            return (age-45.0)/15
        else:
            return 1.0

    def get_fuzzy_set(self, age):
        """Get fuzzy set values of given age."""
        return [self.young(age),
                self.middle(age),
                self.old(age)]

class GIM:
    """GIM- Genre Interestingness Measure"""

    def __init__(self):
        pass

    def gim_a(self, gim, i):
        """Method to get fuzzy set value for very_bad, bad, average, good."""
        if gim <= i - 2 or gim > i:
            return 0.0
        elif i - 2 < gim <= i - 1:
            return gim - i + 2.0
        elif i - 1 < gim <= i:
            return float(i - gim)

    def very_bad(self, gim):
        if gim <= 1.0:
            return 1.0
        else:
            return 0.0

    def bad(self, gim):
        return self.gim_a(gim, 2.0)

    def average(self, gim):
        return self.gim_a(gim, 3.0)

    def good(self, gim):
        return self.gim_a(gim, 4.0)

    def very_good(self, gim):
        return self.gim_a(gim, 5.0)

    def excellent(self, gim):
        if gim <=4.0:
            return 0.0
        else:
            return (gim-4.0)

    def get_fuzzy_set(self, gim_value):
        """Get fuzzy set of gim(list of values) based on given gim value."""
        return [self.very_bad(gim_value),
                self.bad(gim_value),
                self.average(gim_value),
                self.good(gim_value),
                self.very_good(gim_value),
                self.excellent(gim_value)]
