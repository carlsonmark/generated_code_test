from .context import pyapp

import unittest


class BasicTestSuite(unittest.TestCase):
    """Basic test cases."""

    def test_thing1(self):
        self.assertEqual('thing1()', pyapp.thing1())
        return


if __name__ == '__main__':
    unittest.main()
